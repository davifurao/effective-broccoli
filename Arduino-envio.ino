

//Biblioteca do Medidor de Corrente
#include "EmonLib.h"
//Biblioteca do mosquitto
#include <PubSubClient.h> 
//biblioteca do wifi
#include "ESP8266WiFi.h"

//Tensao da rede eletrica
int rede = 220.0;
 
//Pino do sensor SCT
int pino_sct = 1;


//informações do medidor






//Parametros de conexão
const char* ssid = ""; //rede
const char* password = ""; //senha

//MQTT Broker
const char *mqtt_broker = "127.0.0.1"; //Host do broker
const char *topic = "BOBSIEN/teste";//topico a ser subscrito e publicado
const char *mqtt_username = ""; //usuario
const char *mqtt_password = ""; //senha
const int mqtt_port = 1883; //porta

//variaveis

bool mqttStatus = 0; //status da conexão(se falhou ou não)

//objetos
WiFiClient espClient; //é um parametro para determinar que a conexão retornou com exito 
PubSubClient client(espClient); //passando os parametros da conexão wifi para a biblioteca do mqtt

void setup(void) 
{

//Conexão com a rede Wifi


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

//-----------------------------------------------//

  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);   
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 1800/62 = 29. 
  emon1.current(pino_sct, 29);
  //Informacoes iniciais display
  lcd.setCursor(0,0);
  lcd.print("Corr.(A):");
  lcd.setCursor(0,1);
  lcd.print("Pot. (W):");
  
  //conexão com o mqtt
  mqttStatus = connectMQTT();
} 
  
void loop() 
{ 
  //Calcula a corrente  
  double Irms = emon1.calcIrms(1480);
  //Mostra o valor da corrente
  Serial.print("Corrente : ");
  Serial.print(Irms); // Irms
  lcd.setCursor(10,0);
  lcd.print(Irms);
   
  //Calcula e mostra o valor da potencia
  Serial.print(" Potencia : ");
  Serial.println(Irms*rede);
  lcd.setCursor(10,1);
  lcd.print("      ");
  lcd.setCursor(10,1);
  lcd.print(Irms*rede,1);
   
  delay(1000);

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




//https://www.filipeflop.com/blog/medidor-de-energia-eletrica-com-arduino/
