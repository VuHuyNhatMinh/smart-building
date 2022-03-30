
#include <SoftwareSerial.h>
#include "library.h"





SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX PIN_PD2,PIN_PD3
void setup() 
{

/* set up for UART1 */
  UART1.begin(9600);
  while (!UART1);
/* end part */

/* set up for external LED */
  pinMode(PIN_PB4, OUTPUT);
  Serial.begin(9600);
/* end part */

/* set up for headerfile "Wire" */
  Wire.begin();
/* end part */ 

/* set up for light sensor */ 
  lightMeter.begin();
/* end part */

/* set up fot dust sensor */
  pinMode(led_power,OUTPUT);
/* end part */

/* set up for motion sensor */
  pinMode(motion_pin,INPUT);
/* end part */

}

void loop()
{

    if (UART1.available() > 0) 
    {
        UART1.print(ReadDustAndSendToESP());
    }
    delay(500);

    
    if (UART1.available() > 0) 
    {
        UART1.print(ReadMotionAndSendToESP());
    }
    delay(500);
    
    
    if (UART1.available() > 0) 
    {
        UART1.print(ReadLightAndSendToESP());
    }
    delay(500);

    blink();
}
