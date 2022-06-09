#include <SoftwareSerial.h>
#include <Timer.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
Timer t;

int t_Motion_event = 1000;

int motion = 0, totalread = 0;

void setup() {
  // put your setup code here, to run once:
  UART1.begin(9600);
  while (!UART1);

  int Motion_event = t.every(t_Motion_event, Motion, (void*)0);
}

void loop() {
  t.update();
}

void Motion(void *context) {
  if (digitalRead(PIN_PE7))
  { motion++;
    UART1.print("Motion");
    UART1.print(motion);
    UART1.print("   Total  ");
    UART1.println(totalread);
  }
  else
  {
    UART1.print("Non Motion");
    UART1.print("   Total ");
    UART1.println(totalread);
    }

  totalread++;


}
