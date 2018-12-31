// this is a test for the WeMos board

void setup() {
  pinMode(5, OUTPUT); // this is pin D1 on the WeMos board
}

void loop() {
  // light is on for 3 seconds
  digitalWrite(5, HIGH); 
  delay(3000);
  // light is of for 3 seconds
  digitalWrite(5, LOW);
  delay(3000);
}
