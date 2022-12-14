
import paho.mqtt.client as mqtt


HOST= "test.mosquitto.org"
PORT=1883
keepalive=60
bind_address=""
TOPIC=[("teste",0)]#tupla com tópico e QoS. Pode-se adicionar diversos tópicos 
#TOPIC= "teste"

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))



client = mqtt.Client("python3")
client.on_connect = on_connect
client.on_message = on_message


client.connect(HOST, PORT, keepalive,bind_address)

client.loop_forever()
