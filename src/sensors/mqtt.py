import paho.mqtt.client as mqtt
import json
import psycopg2
import uuid
import datetime

mqtt_broker = "broker.hivemq.com"
mqtt_port = 1883
topic = "Year3"

def on_connect(client, userdata, flags, rc):
    print("Connected successfully")
    client.subscribe(topic)

def insert_to_DB(data):
    conn = psycopg2.connect(
        database = 'year3',
        user = 'postgres',
        password = '123456789',
        host = 'localhost',
        port = '5432',
    )

    conn.autocommit = True
    cursor = conn.cursor()

    query = '''INSERT INTO sensors_sensors (id, macaddress, temp, hum, created) 
    VALUES (%s, %s, %s, %s, %s)'''
    id = str(uuid.uuid4())
    created = datetime.datetime.now()
    record = (id, data['ID'], data['Temperature'], data['Humidity'], created)
    cursor.execute(query, record)

    conn.close()

def on_message(client, userdata, msg):
    msg_str = msg.payload.decode("UTF-8")
    msg_json = json.loads(msg_str)
    insert_to_DB(msg_json)
    print(msg_json['Temperature'])


client = mqtt.Client()
client.connect(mqtt_broker, mqtt_port, 60)
client.on_connect = on_connect
client.on_message = on_message
client.subscribe(topic)
# client.loop_forever()
