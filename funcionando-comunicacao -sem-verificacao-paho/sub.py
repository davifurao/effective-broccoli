
import paho.mqtt.client as mqtt


HOST= "test.mosquitto.org"
PORT=1883
keepalive=60
bind_address=""
TOPIC=[("teste",0),("teste2",0)]#tupla com tópico e QoS. Pode-se adicionar diversos tópicos 



def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    for i in range(len(TOPIC)):
        if ((msg.topic,msg.qos)==TOPIC[i]):#comparação do tópico(tupla de tópico e Qos) da mensagem com o tópico(tupla) da variável TOPIC
            with open(f'{TOPIC[i]}.txt','at') as f:#instanciou a variavel f para abrir/criar o arquivo com o nome do tópico(ou qualquer outro que tenha alterado)
                f.write(f'{str(msg.payload)}\n') 
                f.close() 
        
        
    
    print("=============================")
    print("Topic: "+msg.topic)
    print("Payload: "+str(msg.payload))
    print("=============================")

    

    


message='teste'
client = mqtt.Client("python3")
client.on_connect = on_connect
client.on_message = on_message

client.connect(HOST, PORT, keepalive,bind_address)

client.loop_forever()
