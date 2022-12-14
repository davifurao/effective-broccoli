import paho.mqtt.client as mqtt
import time
import random

Broker="mqtt.eclipseprojects.io"
TOPICO="teste"
msg=random.randint(0,30)
PORTA=5650



def on_connect(client,userdata,flags,rc):
    if rc==0:
        client.flag=True #set flag
        print("Connected Ok")
    else:
        print("Bad connection, returned code: ",rc)

mqtt.Client.flag=False#cria a class Flag(usada no teste de conexão)



client= mqtt.Client("P")
client.on_connect= on_connect 
client.connect(Broker, port=PORTA)
client.on_publish= on_publish



def on_publish(client,userdata):#depois do userdata também tem o result
    print("==================")
    #client.publish(TOPICO,msg)
    print("==================")
    pass



while mqtt.Client.flag !=True:
    time.sleep(10) #espera pela conexão

try:
    while True:
       time.sleep(10)
       client.publish(TOPICO,msg)
except KeyboardInterrupt:
    print("\n terminando o programa \n")
    client.disconnect()
    client.loop_stop()





