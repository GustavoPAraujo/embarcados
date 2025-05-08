#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>


AsyncWebServer server(80);
const char* ssid = "Gustavo";
const char* password = "gustavo1234";
const char* DISTANCE_INPUT = "distance";
int distance = 100;   // Default distance value

// Page HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Distancia (cm): <input type="number" name="distance">
    <input type="submit" value="Submit">
  </form><br>
</body></html>
)rawliteral";


void handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void handleRoot(AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html);
}

void handle

void setup() {
    Serial.begin(115200);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Conectando a ");
    Serial.print(ssid);
    Serial.println(" ...");
    
    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries < 20) {
      delay(500);
      Serial.print(".");
      tries++;
    }
    Serial.println();

    int status = WiFi.status();
    if (status == WL_CONNECTED) {
      Serial.println("Conectado!");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    } else {
        Serial.print("Falhou após ");
        Serial.print(tries);
        Serial.print(" tentativas. Código de status: ");
        Serial.println(status);
    }

  // Send web page with input fields to client
  server.on("/", HTTP_GET, handleRoot);

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(DISTANCE_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    distance = inputMessage.toInt();
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
    });
    server.onNotFound(handleNotFound);
    server.begin();
}

void loop() {
    Serial.println(distance);
    delay(200);
}