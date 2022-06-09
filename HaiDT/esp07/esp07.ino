#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <string.h>
#include <stdlib.h>

const char* ssid = "Do Tien Hai";
const char* password = "123456789";
const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "192.168.0.13";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

#define MSG_BUFFER_SIZE 80
char msg[MSG_BUFFER_SIZE];

#define topic "Year3"

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
  int i = 0;
  char s[100];

  strcpy(s, "");

  while (UART2.available() > 0) {

    s[i] = UART2.read();
    i++;
  }
  
  if(i > 0 ){
    s[i] = '\0';
   client.publish(topic, s);

  }
 
}
