#include <Timer.h>
#include <SoftwareSerial.h>

Timer t;
SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX


void setup() {
  // put your setup code here, to run once:

    UART1.begin(9600);  // begin UART
  while (!UART1);

  int getevent = t.every(5000, doSomething, (void*)0);

}

void loop() {
  // put your main code here, to run repeatedly:
t.update();
}

void doSomething(void *context)
{
    UART1.print("2 second tick: millis()=");
    UART1.println(millis());
}
