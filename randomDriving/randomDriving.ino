#define IN1  7  // K1 K2 motor direction
#define IN2  8  // K1 K2 motor direction
#define IN3  11 // K3 K4 motor direction
#define IN4  10 // K3 K4 motor direction
#define ENA  5  // Motor speed
#define ENB  6  // Motor speed

void backward(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,HIGH);
  delay(t);
}

void forward(int t) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW); 
  delay(t);
}

void stopMotor() {
  // motor brake 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
}

void turnLeft(int t) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(t);
}

void turnRight(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(t);
}

void setMotorSpeed(int lspeed,int rspeed) { 
  // speed is between 0 and 255
  analogWrite(ENA,lspeed);
  analogWrite(ENB,rspeed);   
}

void randomDrive() {
  int turnDuration = random(250, 1000);   // turn for between 1/4 and 1 seconds
  int turnDirection = random(0,2);        // random direction to turn in 
  int driveDuration = random(500, 3000);  // drive durration between 1/2 and 3 seconds
  int driveDirection = random(0, 2);      // forward or backward direction

  Serial.print(driveDirection);
  
  // execute turn
  if (turnDirection == 0) {
    turnLeft(turnDuration);
  } else {
    turnRight(turnDuration);
  }

  // excecute drive
  if (driveDirection == 0) {
    forward(driveDuration);
  } else {
    backward(driveDuration);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);

  // sets speed of motor
  setMotorSpeed(150,150);
}

void loop() {
  randomDrive();
}

