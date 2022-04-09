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

/*!
 * @brief Read MAX9814 sensor 
 * 
 */

void readMAX()
{
    unsigned long startMillis= millis();  // Start of sample window
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

    // Collect data for 50 ms (Sufficient lowest frequency 20Hz = 50ms)
    while (millis() - startMillis < 50)
    {
        unsigned int sample = analogRead(0);
        // Toss out spurious readings
        if (sample < 1024)  
        {
            if (sample > signalMax)
            {
                // save just the max levels
                signalMax = sample;  
            }
            else if (sample < signalMin)
            {
                // save just the min levels
                // if not the sample would compare with point zero only
                signalMin = sample;  
            }
        }
    }

    // Peak-to-peak sound level/amplitude
    unsigned int peakToPeak = signalMax - signalMin;  

    // Convert to volts (0 - 3.3) (ADC 10 bit: 0 - 1023)
    double volts = (peakToPeak * 3.3) / 1024; 

    // Covert to decibel (approximately)
    double db = 20*log10(volts/exp(-44*1.0/10));
    Serial.print("Sound: ");
    Serial.print(db);
    Serial.println("db");
}

#endif