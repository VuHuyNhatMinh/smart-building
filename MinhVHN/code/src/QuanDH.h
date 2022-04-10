/**
 *  @file 
 *
 *  @section introduction 
 * 
 *  @section author
 *  
 *  @section library: 
 * 
 */
#ifndef _QUANDH_H_
#define _QUANDH_H_

#include <Arduino.h>

#define dust_pin PIN_PA1
#define led_power PIN_PF1

/**
 * @brief   
 * 
 * @param   mes 
 *          Instance of obj
 */
void readDust(JsonObject mes)
{
    int delay_time=280;
    int delay_time_2=40;
    float off_time=9680; //10000-280-40

    int dustVal=0;
    // char s[32];
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
    
    // String dataString = "Dust: ";
    // dataString += dtostrf(voltage, 9, 4, s);
    // dataString += "V, ";
    // dataString += dtostrf(dustdensity*1000.0, 5, 2, s);
    // dataString += "ug/m3";

    mes["pm25"] = dustdensity;
}

#endif
