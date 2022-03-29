#include <MHZ19.h>
#include <SHT21.h>
#include <DS3231.h>
#include <SoftwareSerial.h>
#include <Timer.h>



SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX
Timer t;


MHZ19 mhz(&UART3);
SHT21 sht;    // SHT21 variable
DS3231  rtc(SDA, SCL);


float temp;   // variable to store temperature
float humidity; // variable to store humidity
int CO2;   // variable to store CO2


void setup() {
  // put your setup code here, to run once:


  Wire.begin();    // begin Wire(I2C)

  UART1.begin(9600);  // begin UART
  while (!UART1);

  UART3.begin(9600);  // begin UART3
  while (!UART3);

  // The following lines can be uncommented to set the date and time
  rtc.begin();
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(13, 0, 0);     // Set the time to 13:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014

  int THevent = t.every(120000, TH, (void*)0);
  int CO2event = t.every(121010, C_CO2, (void*)0);

}



void loop() {
  // put your main code here, to run repeatedly:
  t.update();
}


void TH(void *context)
{

  temp = sht.getTemperature();  // get temp from SHT
  humidity = sht.getHumidity(); // get temp from SHT

  // data trantransmission
  // DS3231 real time
  UART1.print(rtc.getDOWStr()); // send thu trong tuan
  UART1.print(", ");

  UART1.print(rtc.getDateStr());  // Send date
  UART1.print(" - ");
  UART1.println(rtc.getTimeStr());    // Send time
  UART1.print(" || ");

  UART1.print("T: ");      // send Temperature anh Humidity
  UART1.print(temp);
  UART1.print(" || ");
  UART1.print("H: ");
  UART1.println(humidity);
  UART1.print(" ||");



}


void C_CO2(void *context)
{
  
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK)
  {
    CO2 = mhz.getCO2();
    //        UART1.print(F("Temperature: "));
    //        UART1.println(mhz.getTemperature());
    //        UART1.print(F("Accuracy: "));
    //        UART1.println(mhz.getAccuracy());
  }
  else
  {
    UART3.print(F("Error, code: "));
    UART3.println(response);
  }

  // data trantransmission
  // DS3231 real time
  UART1.print(rtc.getDOWStr());   // send thu trong tuan
  UART1.print(", ");

  UART1.print(rtc.getDateStr());  // Send date
  UART1.print(" - ");
  UART1.println(rtc.getTimeStr());    // Send time
  UART1.print(" || ");

  UART1.print(F("CO2: "));    // send CO2
  UART1.print(CO2);
  UART1.print(F(" ||"));


}
