#include <ESP8266WiFi.h>//biblioteca do esp
#include <PubSubClient.h>//biblioteca do mqtt
#include <DHT.h>

const char* ssid = "12345678";//nome da rede
const char* password = "12345678";//senha da rede
const char* mqttServer = "mqtt3.thingspeak.com ";//broker
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
const char* topic_u = "dddfurao_u";//tópico
const char* topic_t = "dddfurao_t";//tópico
//#define SECRET_MQTT_USERNAME "GiEaPBQqIjUbECMfHhckJwI"
//#define SECRET_MQTT_CLIENT_ID "GiEaPBQqIjUbECMfHhckJwI"
//#define SECRET_MQTT_PASSWORD "tGWfQSFptojQWITL/jMpRXtz"

int status = WL_IDLE_STATUS; 
long lastPublishMillis = 0;
int connectionDelay = 1;
int updateInterval = 15;

#define channelID 2024153
const char mqttUserName[] = "GiEaPBQqIjUbECMfHhckJwI"; 
const char clientID[] = "GiEaPBQqIjUbECMfHhckJwI";
const char mqttPass[] = "7l6yfw2AhrFqnTbwXPpyLWV6";
#define ESP8266BOARD

//#ifdef ESP8266BOARD
  //#include <ESP8266WiFi.h>
  //const char* PROGMEM thingspeak_cert_thumbprint = "271892dda426c30709b97ae6c521b95b48f716e1";
//#else

float temperatura;
float umidade;

WiFiClient espClient;
PubSubClient client(espClient);


#define DHTPIN 4 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
   dht.begin(); //Inicializa o sensor DHT11
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqttServer, mqttPort);
  while (!client.connect("NodeMCU", mqttUser, mqttPassword)) {
    Serial.println("Connecting to MQTT...");
    delay(500);
  }
  Serial.println("Connected to MQTT");
}


// Publish messages to a ThingSpeak channel.
void mqttPublish(long pubChannelID, String message) {
  String topicString ="channels/" + String( pubChannelID ) + "/publish";
  client.publish( topicString.c_str(), message.c_str() );
}




void loop() {

// Connect if MQTT client is not connected and resubscribe to channel updates.
  if (!client.connected()) {
     mqttConnect(); 
     mqttSubscribe( channelID );
  }
  
  // Call the loop to maintain connection to the server.
  client.loop(); 
  
  // Update ThingSpeak channel periodically. The update results in the message to the subscriber.
  if ( abs(millis() - lastPublishMillis) > updateInterval*1000) {
    mqttPublish( channelID, (String("field1=")+String(WiFi.RSSI())) );
    lastPublishMillis = millis();
  }
}
  
  //int value = analogRead(A0);//Lê o pino A0, caso queira fazer alguma alteração no projeto, é só mudar o pino(pino de leitura dos dados)
  char message[1000];

  char u[1000];
  char t[1000];
 int temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  //int umidade = dht.readHumidity();
  int umidade = dht.readHumidity(); //Realiza a leitura da umidade
  
  sprintf(u, "%d", temperatura);
  sprintf(t, "%d", umidade);
  
 
  client.publish(topic_u, t);//publica a mensagem
  client.publish(topic_t, u);
  
  delay(1000);//intervalo entre as mensagens
}
