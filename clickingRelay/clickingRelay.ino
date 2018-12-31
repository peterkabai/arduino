 // The WeMos relay requires pin D1
 // that translates to pin 5
 int relayPin = 5;

void setup() {
  // Set the pin mode and set to low
  pinMode(relayPin, OUTPUT); 
  digitalWrite(relayPin, LOW);
}

void loop() {
  // alternate the relay state every 1/2 second
  digitalWrite(relayPin, !digitalRead(relayPin));
  delay(500);
}

