const int trigPin = D5;
const int echoPin = D2;
const int redLed = D7;
const int greenLed = D9;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(greenLed, HIGH);
  digitalWrite(trigPin, LOW);
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
  Serial.print("Dist: ");
  Serial.print(dist);
  Serial.println(" cm");

  if (dist <= 20) {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  } else {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  delay(1000);
}
