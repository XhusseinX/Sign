const int trigPin = 9;
const int echoPin = 10;
const int socketPin = 2;

long duration;
float distance;
unsigned long startTime;
bool objectDetected = false;
bool withinRange = false;
bool x = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(socketPin, OUTPUT);
  digitalWrite(socketPin, LOW);
  Serial.begin(9600);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Check distance
  if (distance < 10.0) {
    if (x) {
      digitalWrite(socketPin, HIGH);
      delay(2000);
      x = false;
    } else {
      if (!withinRange) {
        withinRange = true;
        startTime = millis();
      } else if (millis() - startTime >= 4000 && millis() - startTime <= 6000) {
        objectDetected = true;
      } else if (millis() - startTime < 4000 || millis() - startTime > 6000) {
        objectDetected = false;
      }
    }
  } else {
    if (withinRange) {
      withinRange = false;
      startTime = millis();
    } else if (millis() - startTime >= 4000 && millis() - startTime <= 6000 && objectDetected) {
      x = true;
    } else if (millis() - startTime < 4000 || millis() - startTime > 6000) {
      x = false;
    }
  }

  delay(100);  // Small delay for sensor stability
}
