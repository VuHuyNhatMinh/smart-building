/*******************************************************
*   Author: Vu Huy Nhat Minh 20191973
*******************************************************/
#ifndef _MINH_VHN_
#define _MINH_VHN_

#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void readTCS() 
{
    // uint16_t r, g, b, c, colorTemp, lux;

    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);
    // colorTemp = tcs.calculateColorTemperature(r, g, b);
    // colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    // lux = tcs.calculateLux(r, g, b);

    // Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
    // Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
}


#endif