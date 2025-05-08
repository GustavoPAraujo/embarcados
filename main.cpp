// Setting pin numbers
const int trigPin = D3;
const int echoPin = D4;
const int redLed = D5;
const int greenLed = D11;
// Default distance limit
const int distanceLimit = 20;


void setup() {
    Serial.begin(115200);
    // Loading pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    // Sending start signals
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    Serial.println("Programa iniciado");
}

void loop() {
    long dur = pulseIn(echoPin, HIGH, 30000);

    int raw = digitalRead(echoPin);
    Serial.print("Echo raw: ");
    Serial.print(raw);
    Serial.print(" | Duration: ");
    Serial.println(dur);

    if (dur == 0) {
      Serial.println("Sem pulso detectado");
      delay(200);
      return;
    }
    float dist = dur * 0.034 / 2.0;
    Serial.print("Dist: ");
    Serial.print(dist);
    Serial.println(" cm");

    if (dist <= distanceLimit) {
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
    } else {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
    }

    delay(500);
}