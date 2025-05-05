#include <ESP8266WiFi.h>


const int trigPin = 6;
const int echoPin = 10;
const int redLed = 5;
const int greenLed = 3;
const float distancePotMultiplier = 0.25;
const int distanceLimit = 20;
// WiFi server
WiFiServer server(80); //Initialize the server on Port 80
const char* ssid = "Galaxy A05";
const char* password = "senha123";

void setup() {
  Serial.begin(9600);

  // Setting server
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Retorna o Valor do IP que estará nosso servidor na Rede.
  Serial.print("Usar essa URL : ");
  Serial.print("https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
}