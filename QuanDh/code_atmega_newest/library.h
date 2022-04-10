/*!
 *  @section light sensor: 
 * 
 *  Sensor: BH1759FVI
 *  Vendor:
 *  Github:
 */








#ifndef _LIBRARY_H_
#define _LIFRARY_H_




#include <Wire.h>
#include <BH1750.h>


#define dust_pin PIN_PA1
#define led_power PIN_PF1
#define motion_pin PIN_PE7


BH1750 lightMeter;  //create lightMeter object



String ReadLight(void)
{
    float lux = lightMeter.readLightLevel();
    String data = "Light: ";
    char s[32];
  
    data += dtostrf(lux, 5, 2, s);
    return data;
}


String ReadDust(void)
{
    int delay_time=280;
    int delay_time_2=40;
    float off_time=9680; //10000-280-40

    int dustVal=0;
    char s[32];
    float voltage = 0;
    float dustdensity = 0;

    digitalWrite(led_power,LOW); // power on the LED
    delayMicroseconds(delay_time);
    dustVal=analogRead(dust_pin); // read the dust value
    delayMicroseconds(delay_time_2);
    digitalWrite(led_power,HIGH); // turn the LED off
    delayMicroseconds(off_time);
    
    voltage = dustVal*0.0049;//dustval*5/1024
    dustdensity = 0.172*voltage-0.1;
    
    if (dustdensity < 0 )
    {
        dustdensity = 0;
    }
    
    if (dustdensity > 0.5)
    {
        dustdensity = 0.5;
    }
    
    String dataString = "Dust: ";
    dataString += dtostrf(voltage, 9, 4, s);
    dataString += "V, ";
    dataString += dtostrf(dustdensity*1000.0, 5, 2, s);
    dataString += "ug/m3";

    return dataString;
}


String ReadMotion(void)
{
    int motion = digitalRead(PIN_PE7);

    if(motion)
    {
        return "Vcl co chuyen dong kia lol!!!!";
    }
    else
    { 
        return "Cha thay cai gi chuyen dong ca!!!";
    }
}

void blink(void)
{
    digitalWrite(PIN_PB4, 1); delay(500);
    digitalWrite(PIN_PB4, 0); delay(500);

    digitalWrite(PIN_PB4, 1); delay(500);
    digitalWrite(PIN_PB4, 0); delay(500);
}




#endif
