#include <MHZ19.h>
#include <SHT21.h>
#include <DS3231.h>
#include "Adafruit_TCS34725.h"
#include <BH1750.h>

#include <SoftwareSerial.h>
#include <Timer.h>
#include <Wire.h>


#define dust_pin PIN_PA1
#define led_power PIN_PF1
#define motion_pin PIN_PE7
#define max_pin PIN_PF0


// set time to run all events
int t_Temp_Humid_event = 20000;
int t_CO2_event = 21000;
int t_RGB_event = 22000;
int t_Light_event = 23000;
int t_Motion_event = 24000;
int t_Dust_event = 25000;
int t_Sound_event = 26000;

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX
Timer t;


MHZ19 mhz(&UART3); // set UART for MHZ19
SHT21 sht;    // SHT21 variable
DS3231  rtc(SDA, SCL);
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
BH1750 lightMeter;


void setup() {

  Wire.begin();
  UART1.begin(9600);
  while (!UART1);
  UART3.begin(9600);
  while (!UART3);

  tcs.begin();
  // The following lines can be uncommented to set the date and time
  rtc.begin();
  //  rtc.setDOW(MONDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(22, 31, 30);     // Set the time to 13:00:00 (24hr format)
  //  rtc.setDate(4, 4, 2022);   // Set the date to January 1st, 2014

  // set events
  int Temp_Humid_event = t.every(t_Temp_Humid_event, Read_Temp_Humid, (void*)0);
  
  int CO2_event = t.every(t_CO2_event, Read_CO2, (void*)0);

  int RGB_event = t.every(t_RGB_event, Read_RGB, (void*)0);

  int Light_event = t.every(t_Light_event, Read_Light, (void*)0);

  int Motion_event = t.every(t_Motion_event, Read_Motion, (void*)0);

  int Dust_event = t.every(t_Dust_event, Read_Dust, (void*)0);

  int Sound_event = t.every(t_Sound_event, Read_Sound, (void*)0);
}

void loop() {
  // put your main code here, to run repeatedly:
  t.update();
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

  Real_time();
  // send Temperature anh Humidity
  UART1.print("T: "); UART1.print(sht.getTemperature()); UART1.print(" ");
  UART1.print("H: "); UART1.print(sht.getHumidity()); UART1.println(" ");
}

void Read_CO2(void *context) {      // read data from MHZ19
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK) {

    Real_time();
    UART1.print(F("CO2: "));    // send CO2
    UART1.print(mhz.getCO2()); UART1.println(F(" "));
    //    UART1.print(F("Temperature: "));
    //    UART1.println(mhz.getTemperature());
    //    UART1.print(F("Accuracy: "));
    //    UART1.println(mhz.getAccuracy());
  }
  else {
    UART1.print(F("Error, code: "));
    UART1.println(response);
  }
}

void Read_RGB(void *context) {    // read data from TCS34725
  float r, g, b;
  tcs.getRGB(&r, &g, &b);

  Real_time();
  UART1.print("Red: "); UART1.print(r); UART1.print(" ");
  UART1.print("Green: "); UART1.print(g); UART1.print(" ");
  UART1.print("Blue: "); UART1.print(b); UART1.print(" ");
  UART1.println(" ");
}

void Read_Light(void *context) {    // read data from BH1750
  Real_time();
  UART1.print("Light: "); UART1.print(lightMeter.readLightLevel()); UART1.println(" ");
}

void Read_Motion(void *context) {     // read data from HC - SR501 - PIR

  Real_time();
  if (digitalRead(PIN_PE7))
    UART1.println("Motion");
  else
    UART1.println("Non motion");
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

  Real_time();
  UART1.print("Dust: "); UART1.print(dustdensity * 1000); UART1.println(" ");
}

void Read_Sound(void *context)
{
  int sound = analogRead(max_pin);

  Real_time();
  UART1.print("Sound: "); UART1.print(sound); UART1.println(" ");
}
