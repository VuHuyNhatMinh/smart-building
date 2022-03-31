#include "HaiDT.h"
#include <SoftwareSerial.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX

void setup(void) {
  Wire.begin();    // begin Wire(I2C)

  UART1.begin(9600);  // begin UART
  while (!UART1);

  UART3.begin(9600);  // begin UART3
  while (!UART3);

}

void loop(void) {
    Read_CO2(UART3,UART1);
    Read_Real_time(UART1);
    Read_Temp_Humid(UART1);
}