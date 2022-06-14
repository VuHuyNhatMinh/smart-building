
#include <SoftwareSerial.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
void setup() {
  // put your setup code here, to run once:
  UART1.begin(9600);
  while (!UART1);

  pinMode(PIN_PB4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (UART1.available() > 0) {
    UART1.println("ATMEAG128P");
  }
  delay(1000);
  if (UART1.available() > 0) {
    UART1.println("DO TIEN HAI");
  }
  delay(1000);
  if (UART1.available() > 0) {
    UART1.println("HELLO");
  }

  delay(1000);
  if (UART1.available() > 0) {
    UART1.println("YEAR3");
  }

  digitalWrite(PIN_PB4, 1); delay(1000);
  digitalWrite(PIN_PB4, 0); delay(1000);
}
