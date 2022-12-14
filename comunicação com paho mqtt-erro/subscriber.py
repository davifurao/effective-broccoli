import paho.mqtt.client as mqttClient
import time
import json



IP="test.mosquitto.org"
PORT=1883
TOPICO= "teste"#[("teste",0)]#TUPLA DE TÓPICO E QOS
USUARIO="yourUser"
SENHA="yourPassword"


def on_connect(client, userdata, flags, rc):
    if rc ==0:
        print("conectando ao Broker")
        global Connected #torna a variável global
        Connected = True
    else:
        print("falha na conexão")

def on_message(client, userdata, message):
    data = message.payload
    receive=data.decode("utf-8")
    m_decode = json.loads(receive)


    #print("mensagem recebida: "+str(message.topic))
    #print("=================================")

Connected = False #variável global para o estado da conexão

client = mqttClient.Client("P") #É criado uma nova instância
client.username_pw_set(USUARIO, SENHA=SENHA)  #Caso queira adicionar um usuário e senha descomente essa linha
client.on_connect= on_connect #chama a função callback
client.on_message= on_message
client.connect(IP, PORT)


client.loop_start()  #começa o loop

while Connected != True:  #Espera a conexão
    time.sleep(0.1)

client.subscribe(TOPICO)

try:
    while True:
        time.sleep(1)

except KeyboardInterrupt: #quando clicar CTrl+c
    print("Terminando o programa")
    client.disconnect()
    client.loop_stop()

