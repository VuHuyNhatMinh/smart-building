#include <Arduino.h>
#include <SoftwareSerial.h>

// #include "MHZ19.h"
  

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX

// MHZ19 myMHZ19;
// void Read_Co2(){
//         int CO2;                                        // Buffer for CO2
//         CO2 = myMHZ19.getCO2();                         // Request CO2 (as ppm)

//         if(myMHZ19.errorCode == RESULT_OK)              // RESULT_OK is an alis for 1. Either can be used to confirm the response was OK.
//         {
//             UART1.print("CO2 Value successfully Recieved: ");
//             UART1.println(CO2);
//             UART1.print("Response Code: ");
//             UART1.println(myMHZ19.errorCode);          // Get the Error Code value
//         }
//         else 
//         {
//             UART1.println("Failed to recieve CO2 value - Error");
//             UART1.print("Response Code: ");
//             UART1.println(myMHZ19.errorCode);          // Get the Error Code value
//         }
// };    // MHZ19

void setup(){
  pinMode(PIN_PB4, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial){};
  UART3.begin(9600);
  while (!UART3){};

  // myMHZ19.begin(UART3);

}

void loop(){
  Serial.print("HELLO");

  digitalWrite(PIN_PB4, 1);
  delay(200);
  digitalWrite(PIN_PB4, 0);
  delay(200);
}

