#include <MHZ19.h>
#include <SHT21.h>
#include <DS3231.h>
#include <SoftwareSerial.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX


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

  rtc.begin();

  pinMode(PIN_PB4, OUTPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  char s[100];
  digitalWrite(PIN_PB4, 1); delay(1000);
  digitalWrite(PIN_PB4, 0); delay(1000);


  // read data MHZ19 CO2
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK)
  {
    CO2 = mhz.getCO2();

    //    UART1.print(F("Temperature: "));
    //    UART1.println(mhz.getTemperature());
    //    UART1.print(F("Accuracy: "));
    //    UART1.println(mhz.getAccuracy());
  }
  else
  {
    UART3.print(F("Error, code: "));
    UART3.println(response);
  }


  // read temperature and huimid
  temp = sht.getTemperature();  // get temp from SHT
  humidity = sht.getHumidity(); // get temp from SHT


  // data trantransmission
  // DS3231 real time
  UART1.print(rtc.getDOWStr());
  UART1.print(" ");

  UART1.print(rtc.getDateStr());  // Send date
  UART1.print(" -- ");

  UART1.println(rtc.getTimeStr());    // Send time
  UART1.print(F("CO2: "));
  UART1.print(CO2);
  UART1.print("__");
  UART1.print("T: ");      // print readings
  UART1.print(temp);
  UART1.print("__");
  UART1.print("H: ");
  UART1.println(humidity);

  delay(15000);

}
