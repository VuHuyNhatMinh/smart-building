/**
 *  @file 
 *
 *  @section introduction 
 * 
 *  @section author
 *  
 *  @section library: 
 * 
 *  Sensor: GP2Y_Dust_Sensor_PM2.5 
 * 
 * 
 */
#ifndef _QUANDH_H_
#define _QUANDH_H_

#include <Arduino.h>
#include <string>

#define dust_pin PIN_PA1
#define led_power PIN_PF1

/**
 * @brief   Read GP2Y_Sensor and add to JSON message
 * 
 * @param   mes 
 *          Instance of obj
 */
void readDust(JsonObject mes)
{
    int delay_time=280;     //wait for sample 
    int delay_time_2=40;    //take sample
    float off_time=9680; //10000-280-40, wait for sensor to reset 

    int dustVal=0;
    char s[32];
    float voltage = 0;
    float dustdensity = 0;

    digitalWrite(led_power,LOW); // power on the LED    //sensor start to count dust particles
    delayMicroseconds(delay_time);      //wait 280ms
    dustVal=analogRead(dust_pin); // read the dust value    //read the voltage given out by sensor being equivalent to dust value
    delayMicroseconds(delay_time_2);    //wait for the dust value to be totally read
    digitalWrite(led_power,HIGH); // turn the LED off //sensor stop couting dust particle
    delayMicroseconds(off_time);    //sensor reset
    
    voltage = dustVal*0.0049;  //dustval*5/1024     //turn the dustVal which is the number of step sizes back to voltage given out by sensor
    dustdensity = 0.172*voltage-0.1;                //equation to calculate the dustdensity with the voltage given
    
    if (dustdensity < 0 )                   //0 <= dustdensity <=0.5, other numbers are out of calculation range 
    {
        dustdensity = 0;        
    }
    
    if (dustdensity > 0.5)
    {
        dustdensity = 0.5;
    }

    mes["pm25"] = stof(dtostrf(dustdensity, 5, 3, s));        //unit mg.m3  // min width: 5, num digits after decimal: 3
}


/**
 * @brief   
 * 
 * @param   mes
 *          Instance of obj 
 */
void readPIR(JsonObject mes)
{
    unsigned int cnt = 0;
    for (int i = 0; i < 60 ; i = i + 1)
    {
        if (digitalRead(PIN_PE7))
        {
            cnt = cnt + 1;
        }
    }

    double temp = cnt*1.0/60;

    if (temp > 50.0) 
    {
        mes["motion"] = 1;
    }
    else 
    {
        mes["motion"] = 0;
    }
}
#endif
