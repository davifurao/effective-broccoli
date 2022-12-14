#obviamente precisa do python instalado, na versão 3
#Precisa ser instalado o pip no pc para instalar o paho

import paho.mqtt.client as mqtt #importando a biblioteca do  paho

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("$SYS/#")

    def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("mqtt.eclipseprojects.io", 1883, 60)#broker,port,keepalive
#creio que o bind address será adicionado num server

client.loop_forever()
