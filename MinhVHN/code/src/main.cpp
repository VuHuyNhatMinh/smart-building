#include <Arduino.h>
#include <ArduinoJson.h>
#include "MinhVHN.h"
#include "HaiDT.h"

#include <SoftwareSerial.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX

void setup(void) {
    Serial.begin(9600);

    pinMode(PIN_PA0, OUTPUT);
    digitalWrite(PIN_PA0, LOW);
    tcs.begin();

    Wire.begin();    // begin Wire(I2C)

    UART1.begin(9600);  // begin UART
    while (!UART1);

    UART3.begin(9600);  // begin UART3
    while (!UART3);
}

void loop(void) {
    StaticJsonDocument<200> doc;
    JsonObject obj = doc.to<JsonObject>();
    readTCS(obj);
    readMAX(obj);
    serializeJson(obj, Serial);

    Read_CO2(UART3,UART1);
    Read_Real_time(UART1);
    Read_SHT21(UART1);
}