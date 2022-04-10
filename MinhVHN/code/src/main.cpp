#include <Arduino.h>
#include <ArduinoJson.h>

#include "HaiDT.h"
#include "MinhVHN.h"

void setup(void) {
    Serial.begin(9600);
    while (!Serial)

    UART1.begin(9600);  // begin UART
    while (!UART1);

    UART3.begin(9600);  // begin UART3
    while (!UART3);
    
    /* Initiate TCS34725 */
    pinMode(PIN_PA0, OUTPUT);
    digitalWrite(PIN_PA0, LOW);
    tcs.begin();

    /* Initiate SHT31-D */
    sht31.begin();

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());
}

void loop(void) {
    StaticJsonDocument<200> doc;
    JsonObject obj = doc.to<JsonObject>();
    // readTCS(obj);
    // readMAX(obj);
    // readSHT(obj);
    // readMHZ(obj);
    readCCS(obj);
    serializeJsonPretty(obj, Serial);
}