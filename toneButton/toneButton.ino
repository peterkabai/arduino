int buzzerPin = 9;
int buttonPin = 1;
int frequency = 200; 

void setup() {
  pinMode(pinNumber, INPUT);
  digitalWrite(pinNumber, HIGH);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    tone(buzzerPin, 200);
  } else {
    noTone(buzzerPin);  
  }
}
