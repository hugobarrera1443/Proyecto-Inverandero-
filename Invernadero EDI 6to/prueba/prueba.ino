#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Estudio1";                   // wifi ssid
const char* password =  "Hab417HA";         // wifi password

const char* mqttServer = "192.168.0.113";    // IP adress Raspberry Pi
const int mqttPort = 1883;
const char* mqttUser = "";      // if you don't have MQTT Username, no need input
const char* mqttPassword = "";  // if you don't have MQTT Password, no need input



float temperatura=0;
char valueTemp[15];
String strTemp = "";

float humedad=0;
char valueHum[15];
String strHum = "";


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  Serial.begin(9600);  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

    client.publish("/device/temperatura", "Temperatura Raspberry Pi");
    client.publish("/device/humedad", "Humedad Raspberry Pi");


}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");

}

void loop() {

  
    temperatura=12;  
    strTemp=String(temperatura,1);
    Serial.println(strTemp);
    strTemp.toCharArray(valueTemp, 15);
    client.publish("/device/temperatura",valueTemp );

    humedad=45;  
    strHum=String(humedad,1);
    Serial.println(strHum);
    strHum.toCharArray(valueHum, 15);
    client.publish("/device/humedad",valueHum );
    
    
    delay(1000);
    client.loop();
}
