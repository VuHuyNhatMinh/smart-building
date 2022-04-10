#include <Arduino.h>

#include <SHT21.h>
#include <MHZ19.h>
#include <DS3231.h>



void Read_SHT21(SoftwareSerial UARTset)
{
    SHT21 sht;    // SHT21 variable

    UARTset.print("Temperature: ");      // send Temperature anh Humidity
    UARTset.print(sht.getTemperature());
    UARTset.print("Humidity: ");
    UARTset.print(sht.getHumidity());
    UARTset.println(" ");

}

// Why not use MHZ_CONTINUOUS_MODE

void Read_CO2(SoftwareSerial UARTset1, SoftwareSerial UARTset2)
{
    MHZ19 mhz(&UARTset1);  //set UART for MHZ19

    MHZ19_RESULT response = mhz.retrieveData();

    if (response == MHZ19_RESULT_OK)
    {

        UART1.print(F("CO2: "));                        // CO2 data 
        UART1.println(mhz.getCO2());
        // UARTset2.print(F("Temperature: "));             // orther extra data 
        // UARTset2.println(mhz.getTemperature());
        // UARTset2.print(F("Accuracy: "));
        // UARTset2.println(mhz.getAccuracy());
        UARTset2.println(" ");
    }
    else
    {
        UARTset2.print(F("Error, code: "));
        UARTset2.println(response);
    }

}


void Read_Real_time(SoftwareSerial UARTset)
{
    DS3231  rtc(SDA, SCL);  // set I2C for IC DS3231

    rtc.begin();            // DS3231 begin

    // you can set time again by changing under code
    // rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
    // rtc.setTime(13, 0, 0);     // Set the time to 13:00:00 (24hr format)
    // rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014


    UARTset.print(rtc.getDOWStr()); // send thu trong tuan
    UARTset.print(", ");

    UARTset.print(rtc.getDateStr());  // Send date
    UARTset.print(" - ");
    UARTset.print(rtc.getTimeStr());    // Send time
    UARTset.println(" ");
}



/*!
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
 *  Github: https://github.com/e-radionicacom/SHT21-Arduino-Library
 * 
 *  IC: real time DS3231
 *  link download: http://www.rinkydinkelectronics.com/library.php?id=73
 * 
 * /
