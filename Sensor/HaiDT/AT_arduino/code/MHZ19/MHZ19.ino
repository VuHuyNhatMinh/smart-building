#include <MHZ19.h>
#include <SoftwareSerial.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX
MHZ19 mhz(&UART3);

void setup()
{
  UART1.begin(9600);
  UART3.begin(9600);
}

void loop()
{
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK)
  {
    UART1.print(F("CO2: "));
    UART1.println(mhz.getCO2());
    UART1.print(F("Temperature: "));
    UART1.println(mhz.getTemperature());
    UART1.print(F("Accuracy: "));
    UART1.println(mhz.getAccuracy());
  }
  else
  {
    UART3.print(F("Error, code: "));
    UART3.println(response);
  }


  
  delay(15000);
}
