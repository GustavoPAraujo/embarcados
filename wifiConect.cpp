#include <ESP8266WiFi.h>


const int trigPin = 6;
const int echoPin = 10;
const int redLed = 5;
const int greenLed = 3;
const float distancePotMultiplier = 0.25;
const int distanceLimit = 20;
// WiFi server
WiFiServer server(80); //Initialize the server on Port 80
const char* ssid = "Gustavo";
const char* password = "gustavo1234";

void setup() {
  Serial.begin(9600);

  // Setting server
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  // Retorna o Valor do IP que estará nosso servidor na Rede.
  server.begin();                            // Inicia o servidor
  Serial.print("Acesse em: http://");
  Serial.println(WiFi.localIP());
  
}

void loop() {  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

   client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");        // fecha ao fim
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Status do Rele WEMOS: ");
  // substitua a condição abaixo pela sua lógica real
  if (digitalRead(redLed)) {
    client.print("LIGADO");
  } else {
    client.print("DESLIGADO");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/RELE=LIGADO\">Ligar Rele</a><br>");
  client.println("Click <a href=\"/RELE=DESLIGADO\">Desligar Rele</a><br>");
  client.println("</html>");

  delay(1);
  client.stop(); 
  Serial.println("Página servida.");
}