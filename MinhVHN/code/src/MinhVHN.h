/**
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
 * 
 *  Sensor: MAX9814
 *  Vendor: Adafruit MAX9814
 *  Github: https://github.com/adafruit/Adafruit-MAX9814-AGC-Microphone-PCB
 */

#ifndef _MINHVHN_H_
#define _MINHVHN_H_

#include <Arduino.h>

#include <SPI.h>
#include "Adafruit_TCS34725.h"

/* Initialize tcs object for sensor */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

/**
 *  @brief  Read tcs sensor value and add to message
 * 
 *  @param  mes
 *          Instance of obj
 */
void readTCS(JsonObject mes) 
{
    // Read raw data from sensor
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    // Add to message json object
    mes["red"] = r;
    mes["green"] = g;
    mes["blue"] = b;
}

/**
 *  @brief  Read MAX9814 sensor value and add to message
 * 
 *  @param  mes
 *          Instance of obj
 * 
 */

void readMAX(JsonObject mes)
{
     // Start sampling time
    unsigned long startMillis= millis(); 

    // Max, min value of sound level
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

    // Variable to count noise over 60dB
    unsigned int noise = 0;

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
    // with the microphone sensitivity is -44db, so V RMS / PA is 0.006309
    double db = 20*log10(volts/0.006309);

    if (db > 60.0)
    {
        noise = noise + 1;
    }

    mes["sound"] = noise;
}

#endif