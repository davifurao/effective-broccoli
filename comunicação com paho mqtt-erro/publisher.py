import paho.mqtt.client as mqttClient
import time
import random
import json
#import itens


 
BROKER= "test.mosquitto.org"
porta = 66000
usuario = "yourUser"
SENHA = "yourPassword"
TOPICO="teste"

def on_connect(client, userdata, flags, rc):
 
    if rc == 0:
 
        print("Conectado ao broker")
 
        global Connected                #Use global variable
        Connected = True                #Signal connection 
 
    else:
 
        print("Falha na conexão")

Connected = False   #Variavel global para teste da conexão
 
client = mqttClient.Client("P")               #create new instance
client.username_pw_set(usuario, password=SENHA)    #set username and password
client.on_connect= on_connect                      #attach function to callback
client.connect(BROKER, port=porta)          #connect to broker


 
client.loop_start()        #start the loop
 
while Connected != True:    #Wait for connection
    time.sleep(1)
 
try:
    while True:
        time.sleep(1)
        value = random.randint(0,30)
        client.publish(TOPICO,value)
 
except KeyboardInterrupt:

    print("Saindo")
    client.disconnect()
    client.loop_stop()

    