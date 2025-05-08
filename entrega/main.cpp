#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const int trigPin = D5;
const int echoPin = D2;
const int redLed = D7;
const int greenLed = D9;

const char* ssid = "Gustavo";
const char* password = "gustavo1234";

const char* PARAM_INPUT_1 = "input1";

const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html><head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    </head><body>
    <form action="/get">
      Distancia (cm): <input type="number" name="input1">
      <input type="submit" value="Submit">
    </form><br>
  </body></html>)rawliteral";




  void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(greenLed, HIGH);
  digitalWrite(trigPin, LOW);
}

int distanceBreakPoint = 20;


void setup() {
  Serial.begin(115200);

  // Protobord vars  
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    digitalWrite(greenLed, HIGH);
    digitalWrite(trigPin, LOW);

  // Wifi conection
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
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    distanceBreakPoint = inputMessage.toInt();
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();
}



void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long dur = pulseIn(echoPin, HIGH, 30000);

  int raw = digitalRead(echoPin);
  Serial.print("Echo raw: ");
  Serial.print(raw);
  Serial.print(" | Duration: ");
  Serial.println(dur);

  if (dur == 0) {
    Serial.println("Sem pulso detectado");
    return;
  }

  float dist = dur * 0.034 / 2.0;
  Serial.print("Object Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  Serial.print("Break Point Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  if (dist <= distanceBreakPoint) {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  } else {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  delay(1000);
}
