/*Sử dụng nhiều biến toàn cục,
  ------  PIR Sensor chưa sử dụng
   SD Card chưa sử dụng
  --- CSS811 chỉ hiển thị 1 giá trị là eCO2 = 400 và TVOC  = 0

   Chưa đánh giá được GP2y1010 dust sensor
   Max9814 Sound, chưa đếm tốt, do chưa sử dụng ngắt, đếm ko chuẩn.
   Module hoạt động nhưng chưa có code hoàn chỉnh nên chưa cho chạy,
*/
/************************
    Author: QuangNV42
    Date: 20/11/2021
    Note: Environmental quality monitoring system in smart building
************************/

/*******************************************************************************
   Include
 ******************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_CCS811.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_CCS811.h>
#include <SharpGP2Y10.h>
#include <MHZ19.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <timer.h>
#include <timerManager.h>
#include "WirelessSensorNetwork.h"


Timer timer1;       /* Timer of DS3231 RTC */
Timer timer2;       /* Timer of SHT31 temper and humid */
Timer timer3;       /* Timer of TSL2561 Lux Sensor */
Timer timer4;       /* Timer of RGB Color Sensor */
Timer timer5;       /* Timer of CO2 Mh Z19 Sensor */
Timer timer6;       /* Timer of GP2y1010AuF Dust Sensor */
Timer timer7;       /* Timer of eCO2 and TVOC CSS811 Sensor */
Timer timer8;       /* Timer of Sound MAX9814 Sensor */
Timer timer9;       /* Timer for Task Transmission Data to Module Wifi via UART Protocol */
/*******************************************************************************
   Definitions
 ******************************************************************************/
#define SCREEN_WIDTH 128 /* OLED display width, in pixels */
#define SCREEN_HEIGHT 64 /*  OLED display height, in pixels */
#define OLED_RESET    -1 /* Reset pin # (or -1 if sharing Arduino reset pin) */
#define SCREEN_ADDRESS 0x3C
Adafruit_CCS811 ccs;
Adafruit_SHT31 sht31 = Adafruit_SHT31();
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);/*Initialise with specific int time and gain values */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/*******************************************************************************
   Global Variables
 ******************************************************************************/

uint8_t page_counter = 1 ;          /* Counter to change positions of pages */
uint8_t up = PIN_PA5;               /* Assign Up button for Pin PA5 ATmega128 */
uint8_t down = PIN_PA6;             /* Assign Down button for Pin PA6 ATmega128 */
boolean current_up = LOW;
boolean last_up = LOW;
boolean last_down = LOW;
boolean current_down = LOW;

RTC_DS3231 RTC;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const byte Adafruit_TSL2561 = 0x39;/* Address I2C of TSL2561 */
const byte NumberOfFields = 7;     /* Number of data bytes to read from TSL2561 */
void configureSensor(void)         /* Hardware configuration for the TSL2561  sensor */
{
  tsl.enableAutoRange(true);       /* Auto-gain ... switches automatically between 1x and 16x */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
}

const uint8_t rx_pin = PIN_PE4; /*Serial rx pin assign PIN PE4 of ATmega128, Pin PE4 is Interrupt Pin, so can Mapping as RX pin*/
const uint8_t tx_pin = PIN_PE5; /*Serial tx pin assign PIN PE5 of ATmega128, Pin PE5 is Interrupt Pin, so can Mapping as TX pin*/
MHZ19 *mhz19_uart = new MHZ19(rx_pin, tx_pin);

uint16_t voPin = PIN_PF1;       /*10 bit ADC,Assign voPin of Gp2y1010auf for pin PF1 of ATmega128, return value analog of Dust Sensor*/
uint8_t ledPin = PIN_PA1;       /*PA1 is Digital Pin, ledPin turn on/off IR in dus sensor, so declare ledPin is pin analog PA1 of ATmega128*/
float g_dustDensity = 0;        /*Dust concentration after converting from Analog value*/
SharpGP2Y10 dustSensor(voPin, ledPin);

const uint8_t sampleWindow = 50; /* Sample window width in mS (50 mS = 20Hz)*/
uint16_t sample;  /* Sample is value Analog of Sound Sensor Max9814, due to ADC have accuracy 10 bit, so assign uint16_t */
uint16_t soundAnalogPin = PIN_PF0; /* Pin PF0 is Analog pin of ATmega128L */

const byte interruptPin = INT7;  /* Pin Interrupt use for PIR sensor HC - SR 501 */
volatile byte pinStatus = LOW;      /* Assign status of pin is Low */

uint32_t theUnixtime = 0;
uint8_t theDayOfWeek = 0;
uint16_t theYear = 0;
uint8_t theMonth = 0;
uint8_t theDay = 0;
uint8_t theHour = 0;
uint8_t theMinute = 0;
uint8_t theSecond = 0;

float g_Temper = 0;         /*Temperature Global Variable*/
float g_Humid = 0;          /*Humidity Global Variable*/
uint16_t g_CO2 = 0;         /*CO2 Mh Z19  Global Variable*/
uint8_t g_noiseEvent = 0;   /*NoiseEvent From MAX9814 Global Variable*/
uint16_t g_eCO2 = 0;          /*eCO2 CCS811 Global Variable*/
uint16_t g_TVOC = 0;          /*TVOC CCS811 Global Variable*/
uint16_t g_Lux = 0;         /*Lux TSL2561 Global Variable*/
uint16_t g_Red, g_Green, g_Blue, c, colorTemp, luxTCS;/* Red, Green, Blue Global Variable*/
uint8_t g_countPeople = 0;
/*******************************************************************************
   VOID SETUP();
 ******************************************************************************/
void setup() {
  Wire.begin();               /* Initation I2C protocol*/
  Serial1.begin(9600);        /*initialize Serila1 UART1 for data transmission*/
  RTC.begin();                /* Initation RTC DS3231 Sensor*/
  /* When time needs to be set on a new device, or after a power loss, the 
   following line sets the RTC to the date & time this sketch was compiled */
  //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  sht31.begin(0x44);          /* Initation SHT31 Sensor*/
  tsl.begin();                /* Initation TSL2561 Sensor*/
  configureSensor();          /* Setup the TSL2561 sensor gain and integration time */
  ccs.begin();                /* Initation CCS811 Sensor*/
  tcs.begin();                /* Initation TCS34725 Sensor*/
  mhz19_uart->begin(rx_pin, tx_pin);      /* Initation MH Z19 Sensor*/
  mhz19_uart->setAutoCalibration(false);  /* Not Calibretion CO2 sensor*/

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /*Initation the OLED display*/
  display.clearDisplay();                    /*Clear screen SSD1306*/
  display.display();                         /*Allow display*/
  pinMode(PIN_PA0, OUTPUT); /*Off led control Pin of TCS34725,the led off for incident light measurement..*/
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), NumberOfPeople, HIGH);
  /* Set the interval in milliseconds */
  timer1.setInterval(1000);   /* Sample time of DS3231 RTC */
  timer2.setInterval(10000);  /* Sample time of SHT31 temper and humid */
  timer3.setInterval(1000);    /* Sample time of TSL2561 Lux Sensor */
  timer4.setInterval(1000);    /* Sample time of RGB Color Sensor */
  timer5.setInterval(10000);   /* Sample time of CO2 Mh Z19 Sensor */
  timer6.setInterval(10000);   /* Sample time of GP2y1010AuF Dust Sensor */
  timer7.setInterval(10000);   /* Sample time of eCO2 and TVOC CSS811 Sensor */
  timer8.setInterval(200);  /* Sample time of Sound MAX9814 Sensor */
  timer9.setInterval(60000);  /* Sample timer of Data Transmission UART */
  /* Set our callback function */
  timer1.setCallback(GetDateTimeValue);
  timer2.setCallback(GetTemperHumidValue);
  timer3.setCallback(GetLux);
  timer4.setCallback(GetRedGreenBlueValue);
  timer5.setCallback(GetCO2Value);
  timer6.setCallback(GetDustDensityValue);
  timer7.setCallback(GeteCO2TVOCValue);
  timer8.setCallback(GetNoiseEventsValue);
  timer9.setCallback(DataTransmission);

  /* Start all the timers */
  TimerManager::instance().start();
}

/*******************************************************************************
   FUNCITION
 ******************************************************************************/
/*
    @brief  Prevents key bounces due to the physical properties of the buttons
    @return None
*/
/*---- De-bouncing function for all buttons----*/
boolean debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}
/*
    @brief function to move between pages by buttons
    @return None
*/
void UpDownButton(void)
{
  current_up = debounce(last_up, up);          /*Debounce for Up button*/
  current_down = debounce(last_down, down);    /*Debounce for Down button*/
  /*----Page counter function to move pages----*/
  if (last_up == LOW && current_up == HIGH)    /*When up button is pressed //Page Up*/
  {
    display.clearDisplay();                    /*When page is changed, lcd clear to print new page*/
    if (page_counter < 2)                      /*Page counter never higher than 3(total of pages)*/
    {
      page_counter = page_counter + 1;         /*Page up*/
    }
    else
    {
      page_counter = 2;
    }
  }

  last_up = current_up;

  if (last_down == LOW && current_down == HIGH) { /*When down button is pressed*/
    display.clearDisplay();                       /*When page is changed, lcd clear to print new page*/
    if (page_counter > 1)                         /*Page counter never lower than 1 (total of pages)*/
    {
      page_counter = page_counter - 1;            /*Page down*/

    }
    else
    {
      page_counter = 1;
    }
  }

  last_down = current_down;
}
/*
    @brief The function count number of people in the room
    @return None
*/
void NumberOfPeople()
{
  g_countPeople++;
}
/*
    @brief The function takes the value of date, time, day
    @return None
*/
void GetDateTimeValue(void)
{
  DateTime now = RTC.now();
  theUnixtime = now.unixtime();
  theDayOfWeek = now.dayOfTheWeek();
  theYear = now.year();
  theMonth = now.month();
  theDay = now.day();
  theHour = now.hour() ;
  theMinute = now.minute() ;
  theSecond = now.second();
}
/*
    @brief function to move between pages by buttons
    @return None
*/
void GetTemperHumidValue(void)
{
  g_Temper = sht31.readTemperature();
  g_Humid = sht31.readHumidity();
}
/*
    @brief Function to read parameter values of light intensity
    @return None
*/
void GetLux(void)
{
  sensors_event_t event;
  tsl.getEvent(&event);
  g_Lux = event.light ;
}
/*
    @brief Function to read parameter values of Red, Green, Blue  color of Light
    @return None
*/
void GetRedGreenBlueValue(void)
{
  tcs.getRawData(&g_Red, &g_Green, &g_Blue, &c);
  colorTemp = tcs.calculateColorTemperature(g_Red, g_Green, g_Blue);
  luxTCS = tcs.calculateLux(g_Red, g_Green, g_Blue);
}
/*
    @brief Function to read parameter values of CO2 concentration of the air
    @return None
*/
void GetCO2Value(void)
{
  measurement_t m = mhz19_uart->getMeasurement();
  g_CO2 = m.co2_ppm;
}
/*
    @brief Function to read parameter values of Dust concentration of the air
    @return None
*/
void GetDustDensityValue(void)
{
  g_dustDensity = dustSensor.getDustDensity(); /* (0.5V = 0.1mg/m3) according to datasheet, in fact, Linear equations,\
                                                  dustDensity = 0.17 * (Vo * Vpd) - 0.1 */
}
/*
    @brief Function to read parameter values of eCO2(Equivalent CO2) and TVOC( Volatitle organic compounds) concentration of the air
    @return None
*/
void GeteCO2TVOCValue(void)
{
  if (ccs.readData())
  {
    if (!ccs.readData())
    {
      g_eCO2 = ccs.geteCO2();
      g_TVOC = ccs.getTVOC();
    }
  }
}
/*
    @brief Function to Count the number of times the noise level exceeds the allowable threshold
    @return None
*/
void GetNoiseEventsValue(void)
{
  unsigned long startMillis = millis(); /* Start of sample window */
  unsigned int peakToPeak = 0;   /* peak-to-peak level */
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  /* collect data for 50 mS, then average the values*/
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(soundAnalogPin);
    if (sample < 1024)  /*  toss out spurious readings */
    {
      if (sample > signalMax)
      {
        signalMax = sample;  /* save just the max levels */
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  /*  save just the min levels */
      }
    }
  }
  peakToPeak = signalMax - signalMin;  /* max - min = peak-peak amplitude */
  double volts = (peakToPeak * 3.3) / 1024;  /*  convert to volts */
  if (volts > 1.5) {
    g_noiseEvent++;
  }
}
/*
    @brief Function to display date, time, day
    @return None
*/
void DateTimeDisplay(void)
{
  display.clearDisplay();                     /* Clear all in Screen, prepare Print new data */
  display.setTextSize(1);                     /* Set text Size là 1 */
  display.setTextColor(WHITE);                /* Set Text color is White */
  display.setCursor(40, 0);
  display.print(daysOfTheWeek[theDayOfWeek]); /* Display the Day of the week as Text */

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(4, 14);
  display.print(theDay, DEC);
  display.print(":");
  display.print(theMonth, DEC);
  display.print(":");
  display.print(theYear, DEC);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(16, 35);
  display.print(theHour, DEC);
  display.print(":");
  display.print(theMinute, DEC);
  display.print(":");
  display.print(theSecond, DEC);

  display.display();
}
/*
    @brief  Displays all measured environmental parameters
    @return None
*/
void DisplayAllIndex(void)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("eCO2:");
  display.print(g_eCO2);

  display.setCursor(64, 0);
  display.print("TVOC:");
  display.print(g_TVOC);

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 13);
  display.print("T:");
  display.print(g_Temper);                  /* Temperature Index */
  // display.drawCircle(44, 13, 1, WHITE);
  display.print(" C");
  display.setCursor(64, 13);
  display.print("H:");
  display.print(g_Humid);                   /* Humidity Index */
  display.print(" %");

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 28);
  display.print("Lux:");                   /* Light intensity Index */
  display.print(g_Lux);

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(64, 28);
  display.print("Noise:");                 /* Number of times the noise level exceeds the threshold in a period of time */
  display.print(g_noiseEvent);

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 57);
  display.print("R:");
  display.print(g_Red);                   /* Red Index */
  display.setCursor(42, 57);
  display.print("G:");
  display.print(g_Green);                 /* Green Index */
  display.setCursor(84, 57);
  display.print("B:");
  display.print(g_Blue);                  /* Blue Index */


  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 43);
  display.print("CO2:");
  display.print(g_CO2);                  /*CO2  concentration */
  //display.print("ppm");

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(64, 43);
  display.print("DUST:");
  display.print(g_dustDensity);         /*Dust   concentration */
  //display.print(" mg/m3");

  display.display();                    /*Allow display data */
}
/*
    @brief Function to transfer data from microcontroller to Wifi module via UART protocol
    @return None
*/
void DataTransmission(void)
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["sensorid1"] = 1;
  root["time"] = theUnixtime;           /* the number of seconds that have elapsed since January 1, 1970 (midnight UTC/GMT) */
  root["temperature"] = g_Temper;       /* The unit of temperature is °C */
  root["humidity"] = g_Humid;           /* The unit of humidity is % */
  root["light"] = g_Lux;                /* 16 digital Output about 1 - 40k lux, The unit of light intensity is lux */
  root["Red"] = g_Red;
  root["Green"] = g_Green;
  root["Blue"] = g_Blue;
  root["co2"] = g_CO2;                  /* (0 -> 5000ppm)datasheet unit ppm parts per million (one/ million)  */
  root["sound"] = g_noiseEvent;         /* number noise over threshold per time */
  root["eCO2"]  = g_eCO2;               /* 400 -> 29206ppm datasheet*/
  root["TVOC"] = g_TVOC;                /* 0 -> 32768ppb  parts per billion datasheet*/
  root["dust"] = g_dustDensity;         /* 0 -> 5V,dust 0 - > 0.8 mg/m3 datasheet, unit mg/m3*/
  root["people"] = g_countPeople;       /* number people in room per Period*/
  if (Serial1.available() > 0)
  {
    root.printTo(Serial1);
  }
  g_noiseEvent = 0;
  g_countPeople = 0;
}
/*******************************************************************************
   VOID LOOP();
 ******************************************************************************/
void loop()
{
  /* Update all the timers at once */
  TimerManager::instance().update();

  UpDownButton();             /* the program service moves between screens*/
  digitalWrite(PIN_PA0, LOW); /* Off Led of TCS34725 Sensor, so it will measuament  incident light measurement */
  /* Program select display screen Date Time Or All Index environment */
  switch (page_counter)
  {
    case 1:
      {
        DateTimeDisplay();  /* Date Time Screen */
        break;
      }
    case 2:
      {
        DisplayAllIndex(); /*  All Index Environment Screen */
        break;
      }
  }

}/*END OF FILE*/
