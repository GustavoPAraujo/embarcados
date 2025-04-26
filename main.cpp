const int trigPin = D5;
const int echoPin = D2;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  } else {
    float dist = dur * 0.034 / 2.0;
    Serial.print("Dist: ");
    Serial.print(dist);
    Serial.println(" cm");
  }

  delay(200);
}
