#include "ESP8266WiFi.h" // problema de integração
#include <PubSubClient.h>

//Parametros de conexão
const char* ssid = ""; //rede
const char* password = ""; //senha

//MQTT Broker
const char *mqtt_broker = "test.mosquitto.org"; //Host do broker
const char *topic = "BOBSIEN/teste";//topico a ser subscrito e publicado
const char *mqtt_username = ""; //usuario
const char *mqtt_password = ""; //senha
const int mqtt_port = 1883; //porta

//variaveis

bool mqttStatus = 0; //status da conexão(se falhou ou não)

//objetos
WiFiClient espClient; //é um parametro para determinar que a conexão retornou com exito 
PubSubClient client(espClient); //passando os parametros da conexão wifi para a biblioteca do mqtt

//Prototipos
bool connectMQTT();
void callback(char *topic, byte *payload, unsigned int length);

void setup(void)
{
  Serial.begin(9600);

  //conectar
  WiFi.begin(ssid,password);

  //aguardando conexão
  Serial.println();
  Serial.print("Conectando");
  while(WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //Envia IP através da UART
  Serial.println(WiFi.localIP());
  mqttStatus = connectMQTT();

}
void loop() {
  if(mqttStatus){
    client.loop();//problema de loop()
  }
}


bool connectMQTT() {
  byte tentativa = 0;
  client.setServer(mqtt_broker,mqtt_port);
  client.setCallback(callback);

  do{
    String client_id = "BOBSIEN-";
    client_id += String(WiFi.macAddress());

    if(client.connect(client_id.c_str(), mqtt_username,mqtt_password)) {
      Serial.println("Exito na conexão:");
      Serial.printf("Cliente %s conectado ao broker\n", client_id.c_str());
    }else{
      Serial.print("Falha ao conectar: ");
      Serial.print(client.state());
      Serial.println();
      Serial.print("tentativa: ");
      Serial.println(tentativa);
      delay(2000);
    }
    tentativa++;
  
  }while(!client.connected()&& tentativa<5);

  if(tentativa<5) {
    //publish and subscribe
    client.publish(topic,"{300v}");
    client.subscribe(topic);
    return 1;//verificar se o algarismo 1 está inserido
  } else {
    Serial.println("Não conectado");
    return 0;
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for(int i=0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-------------------------");
}





