/*!
 *  @file MinhVHN.h
 *
 *  @section introduction 
 * 
 *  @section author
 *  
 *  Vu Huy Nhat Minh 20191973
 * 
 *  @section library: 
 * 
 *  Sensor: TCS34725
 *  Vendor: Adafruit TCS 34725 
 *  Github: https://github.com/adafruit/Adafruit_TCS34725
 */
#ifndef _MINHVHN_H_
#define _MINHVHN_H_

#include <Arduino.h>

#include <SPI.h>
#include "Adafruit_TCS34725.h"

/* Initialize tcs object for sensor */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

/*!
 *  @brief Read tcs sensor value and add to message
 */
void readTCS() 
{
    float r, g, b;
    tcs.getRGB(&r, &g, &b);
    Serial.print("Red: "); Serial.print(r); Serial.print(" ");
    Serial.print("Green: "); Serial.print(g); Serial.print(" ");
    Serial.print("Blue: "); Serial.print(b); Serial.print(" ");
    Serial.println(" ");
}

void readMAX()
{
    int sound = analogRead(PIN_PF0);
    Serial.print("Sound: "); 
    Serial.println(sound);
}

#endif