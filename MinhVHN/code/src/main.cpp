#include <Arduino.h>
#include <ArduinoJson.h>

#include "HaiDT.h"
#include "MinhVHN.h"
#include "QuanDH.h"

void setup(void) {
    Serial.begin(9600);
    // while (!Serial)

    UART1.begin(9600);  // begin UART1
    // while (!UART1);

    UART3.begin(9600);  // begin UART3
    // while (!UART3);
    
    /* Initiate TCS34725 */
    pinMode(PIN_PA0, OUTPUT);
    digitalWrite(PIN_PA0, LOW);
    tcs.begin();

    /* Initiate SHT31-D */
    sht31.begin();

    /* Initiate CCS811 */
    ccs.begin();

    /* Initiate TSL2561 */
    tsl.begin();
    tsl.enableAutoRange(true);
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

void loop(void) {
    StaticJsonDocument<200> doc;
    JsonObject obj = doc.to<JsonObject>();
    readTCS(obj);
    readMAX(obj);
    readSHT(obj);
    readMHZ(obj);
    readCCS(obj);
    readTSL(obj);
    readDust(obj);
    readPIR(obj);
    serializeJsonPretty(obj, Serial);
}