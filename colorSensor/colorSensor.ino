#define sensorPin 3

// sets previous state of the sensor to high
int prevSensorValue = HIGH;

// prints sensor value if it has changed
void printSensorValue() {
  int sensor = digitalRead(sensorPin);
  if (sensor == HIGH && prevSensorValue != HIGH) {
    Serial.println("High");
    prevSensorValue = HIGH;
  } 
  if (sensor == LOW && prevSensorValue != LOW) {
    Serial.println("Low");
    prevSensorValue = LOW;
  }
}

void setup() {
  pinMode(sensorPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  printSensorValue();
}
