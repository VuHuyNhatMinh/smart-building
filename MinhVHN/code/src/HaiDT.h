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
 *  Sensor: MHZ19 
 *  Github: https://github.com/strange-v/MHZ19
 * 
 *  Sensor: SHT21
 *  Vendor: Adafruit SHT31
 *  Github: https://github.com/e-radionicacom/SHT21-Arduino-Library
 * 
 *  IC: real time DS3231
 *  link download: http://www.rinkydinkelectronics.com/library.php?id=73
 * 
 */
 
#ifndef _HAIDT_H_
#define _HAIDT_H_

#include <Arduino.h>

#include <Adafruit_SHT31.h>

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void readSHT(JsonObject mes)
{
    // send Temperature anh Humidity
    mes["temp"] = sht31.readTemperature();
    mes["hum"] = sht31.readHumidity();
}

#endif