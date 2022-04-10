/**
 *  @file haiDT.h
 *
 *  @section introduction 
 * 
 *  @section author
 *  
 *  DO TIEN HAI 20191811
 * 
 *  @section library: 
 * 
 *  Sensor: SHT31-D
 *  Vendor: Adafruit SHT31
 *  Github: https://github.com/adafruit/Adafruit_SHT31
 * 
 *  Sensor: MHZ19 
 *  Github: https://github.com/strange-v/MHZ19
 * 
 *  IC: real time DS3231
 *  link download: http://www.rinkydinkelectronics.com/library.php?id=73
 * 
 */
 
#ifndef _HAIDT_H_
#define _HAIDT_H_

#include <Arduino.h>

#include <Adafruit_SHT31.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX

Adafruit_SHT31 sht31 = Adafruit_SHT31();
MHZ19 mhz(&UART3);

void readSHT(JsonObject mes)
{
    // Read temperature anh humidity value
    mes["temp"] = sht31.readTemperature();
    mes["hum"] = sht31.readHumidity();
}

void readMHZ(JsonObject mes)
{
    // Read CO2 value
    MHZ19_RESULT response = mhz.retrieveData();
    if (response == MHZ19_RESULT_OK)
    {
        mes["co2"] = mhz.getCO2();
    }
}

#endif