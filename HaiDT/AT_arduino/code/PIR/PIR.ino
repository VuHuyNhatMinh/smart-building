#include <SoftwareSerial.h>
#include <Timer.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
Timer t;

int t_Motion_event = 1000;
int t_Read_Motion_event = 60000;

int motion = 0, totalread = 0;

void setup() {
  // put your setup code here, to run once:
    UART1.begin(9600);
  while (!UART1);
  
  int Motion_event = t.every(t_Motion_event, Motion, (void*)0);
  int Read_Motion_event = t.every(t_Read_Motion_event, Read_Motion, (void*)0);
}

void loop() {
  // put your main code here, to run repeatedly:
t.update();
}

void Motion(void *context) {
  if (digitalRead(PIN_PE7))
    motion++;

  totalread++;
}

void Read_Motion(void *context) {     // read data from HC - SR501 - PIR

  if ((float)motion / totalread >= 0.5) // nếu trong 1p có 30/60 lần đọc chuyển động thì báo là có chuyển động
  { UART1.println("Motion");
    motion = 0;
    totalread = 0;
  }
  else
    UART1.println("Non Motion");

}
