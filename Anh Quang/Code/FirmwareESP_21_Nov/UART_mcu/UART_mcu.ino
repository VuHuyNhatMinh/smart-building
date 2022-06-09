#include <SoftwareSerial.h>
SoftwareSerial s(13, 15);
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
/* Update these with values suitable for your network. */
const char* ssid = "Quang Nguyen";
const char* password = "nguyenvanquang02091998";
const char* mqtt_server = "broker.mqttdashboard.com";
const char* mqttUser = "quangnguyen";
const char* mqttPassword = "quangnguyen";
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
  /* We start by connecting to a WiFi network */
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect()
{
  while (!client.connected())
  { /*  Loop until we're reconnected */
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";/*  Create a random client ID */
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
    }
  }
}

void setup()
{
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  while (!Serial) continue;
}

void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
  {
    return;
  }
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);


  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  char JSONmessageBuffer[1000];
  root.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  client.publish("node10", JSONmessageBuffer, false);
  Serial.print("JSON: ");
  Serial.println(JSONmessageBuffer);
}
