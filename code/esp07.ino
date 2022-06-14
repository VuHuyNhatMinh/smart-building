#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <string.h>
#include <ArduinoJson.h>


//const char* ssid = "MINHCHAU_2.4";
//const char* password = "ETHANhunt(-)123";

const char* ssid = "Nha Tro 21B_T2";
const char* password = "dotienhai";

const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "192.168.31.215";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


#define topic "year3"

SoftwareSerial UART2(13, 15); // khai bao uart2 cua esp

void setup_wifi()
{
  /*
     Initializing Wifi connections
     When wifi is connected, turn LED_BUILTIN off.
  */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }
}

void reconnect() {
  /* Connecting to MQTT server*/
  // Loop until we're reconnected
  while (!client.connected())
  {
    // Signalizing a MQTT connection
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);

    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      /* If connection to MQTT server is successful, turn LED_BUILTIN on */
      digitalWrite(LED_BUILTIN, LOW);
      // Resubscribe to topic
      client.subscribe(topic);
    }
    else
    {
      /* If connection to MQTT server is failed, turn LED_BUILTIN off */
      digitalWrite(LED_BUILTIN, HIGH);
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  // Connecting to Wifi
  pinMode(BUILTIN_LED, OUTPUT);
  setup_wifi();

  // Connecting to MQTT server
  client.setServer(mqtt_server, mqtt_port);
  UART2.begin(9600);
  Serial.begin(9600);


}
void loop()
{
  // Reconnecting to MQTT server
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(200);

  /* Publishing a message to MQTT server */
  digitalWrite(LED_BUILTIN, HIGH);

  /* nhan du lieu tu uart */
  /* Finishing publish */

  if (UART2.available())
  {
    //     Allocate the JSON document
    //     This one must be bigger than for the sender because it must store the strings
    StaticJsonDocument<300> doc;

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, UART2);

    if (err == DeserializationError::Ok)
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      char msg[300];
      serializeJson(doc, msg);
      Serial.println(msg);
      client.publish(topic, msg);

    }
    else
    {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());

      // Flush all bytes in the "link" serial port buffer
      while (UART2.available() > 0)
        UART2.read();
    }
  }



  }
