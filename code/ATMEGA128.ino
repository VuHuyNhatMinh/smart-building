#include <MHZ19.h>
#include <SHT21.h>
#include <DS3231.h>
#include "Adafruit_TCS34725.h"
#include <BH1750.h>
#include "Adafruit_CCS811.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Timer.h>
#include <Wire.h>


#define dust_pin PIN_PA1
#define led_power PIN_PF1
#define motion_pin PIN_PE7
#define max_pin PIN_PF0

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX
Timer t_read, t_send;


// set time to run all events
int t_Temp_Humid_event = 10000;
int t_CO2_event = 10000;
int t_RGB_event = 10000;
int t_Light_event = 10000;
int t_Motion_event = 1000;
int t_Read_Motion_event = 30000;
int t_Dust_event = 10000;
int t_Sound_event = 10000;
int t_Gas_event = 10000;
int t_Send_Data_event = 10000;

MHZ19 mhz(&UART3); // set UART for MHZ19
DS3231  rtc(SDA, SCL);
BH1750 lightMeter;
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
float motiontime = 0, totalread = 0;


float temp = 0, humid = 0;
int CO2 = 0;
float r = 0, g = 0, b = 0;
float light = 0;
bool motion = 0;
int sound = 0;
float dust = 0;
int CO2_gas = 0, TVOC = 0;




void setup() {

  Wire.begin();
  UART1.begin(9600);
  while (!UART1);
  UART3.begin(9600);
  while (!UART3);
  
  tcs.begin();
  // The following lines can be uncommented to set the date and time
  rtc.begin();
//    rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
//    rtc.setTime(16, 39, 30);     // Set the time to 16:21:30 (24hr format)
//    rtc.setDate(20, 5, 2022);   // Set the date to 25/5/2022
  lightMeter.begin();
  
  // set events
  int Temp_Humid_event = t_read.every(t_Temp_Humid_event, Read_Temp_Humid, (void*)0);

  int CO2_event = t_read.every(t_CO2_event, Read_CO2, (void*)0);

  int RGB_event = t_read.every(t_RGB_event, Read_RGB, (void*)0);

  int Light_event = t_read.every(t_Light_event, Read_Light, (void*)0);

  int Motion_event = t_read.every(t_Motion_event, Motion, (void*)0);
  int Read_Motion_event = t_read.every(t_Read_Motion_event, Read_Motion, (void*)0);

  int Dust_event = t_read.every(t_Dust_event, Read_Dust, (void*)0);

  int Sound_event = t_read.every(t_Sound_event, Read_Sound, (void*)0);

  int Gas_event = t_read.every(t_Gas_event, Read_Gas, (void*)0);

  int Send_Data_event = t_send.every(t_Send_Data_event, Send_Data, (void*)0);

}

void loop() {
  // put your main code here, to run repeatedly:
  t_read.update();
  t_send.update();
}


void Real_time() {    // DS3231 real time

  UART1.print(rtc.getDOWStr()); // send thu trong tuan
  UART1.print(", ");
  UART1.print(rtc.getDateStr());  // Send date
  UART1.print(" - ");
  UART1.print(rtc.getTimeStr());    // Send time
  UART1.print(" || ");
}

void Read_Temp_Humid(void *context) {   // read data from Sht21
  SHT21 sht;    // SHT21 variable
  temp = sht.getTemperature();
  humid = sht.getHumidity();
}

void Read_CO2(void *context) {      // read data from MHZ19
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK) {
      CO2 = mhz.getCO2();
  }
  else {
    UART1.print(F("CO2 Error "));
    UART1.println(response);
  }
  
}

void Read_RGB(void *context) {    // read data from TCS34725
  tcs.getRGB(&r, &g, &b);
  }

void Read_Light(void *context) {    // read data from BH1750

    light = lightMeter.readLightLevel();
}

void Motion(void *context) {
  if (digitalRead(PIN_PE7))
    motiontime++;

  totalread++;
}

void Read_Motion(void *context) {     // read data from HC - SR501 - PIR
  
  if (motiontime/totalread >= 0.5) // nếu trong 1p có 50% lần đọc chuyển động thì báo là có chuyển động
    motion = 1;
  else
    motion = 0;
    
  motiontime = 0;
  totalread = 0;
}
void Read_Dust(void *context) {   // read data from GP2Y DUST PM2.5

  int dustVal = 0;
  float voltage = 0;
  float dustdensity = 0;
  
  digitalWrite(led_power, LOW); // power on the LED
  delayMicroseconds(280);
  dustVal = analogRead(dust_pin); // read the dust value
  delayMicroseconds(40);
  digitalWrite(led_power, HIGH); // turn the LED off

  voltage = dustVal * 0.0049; //dustval*5/1024
  dustdensity = 0.172 * voltage - 0.1;

  if (dustdensity < 0)
    dustdensity = 0;
  if (dustdensity > 0.5)
    dustdensity = 0.5;
    
  dust = dustdensity * 1000;
}

void Read_Sound(void *context)
{
  sound = analogRead(max_pin);
}

void Read_Gas(void *context)
{
  Adafruit_CCS811 ccs;
  
  if(ccs.available()){
      if(!ccs.readData()){
        CO2_gas = ccs.geteCO2();
        TVOC = ccs.getTVOC();
      }
  }
}


void Send_Data(void *context)
{
    char msg[300];
  StaticJsonDocument<300> doc;
    doc["REG"] = r;
    doc["GREEN"] = g;
    doc["BLUE"] = b;
    doc["LIGHT"] = light;
    doc["CO2"] = CO2;
    doc["DUST"] = dust;
    doc["TVOC"] = TVOC;
    doc["MOTION"] = motion;
    doc["SOUND"] = sound;
    doc["TEMPERATURE"] = temp;
    doc["HUMIDITY"] = humid;
    doc["STATUS"] = 0;
  serializeJson(doc, UART1);
}
