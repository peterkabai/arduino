#include <IRremote.h>
#include <TonePlayer.h>
#include <math.h> 
#include <string.h>

// sets pins
#define irPin 4
#define buzzerPin 9
#define IN1  7  // K1 motor direction
#define IN2  8  // K1 motor direction
#define IN3  11 // K3 motor direction
#define IN4  10 // K3 motor direction
#define ENA  5  // Motor speed
#define ENB  6  // Motor speed

// IR codes for each numbered button
#define IR_1 0x00FFA25D
#define IR_2 0x00FF629D
#define IR_3 0x00FFE21D
#define IR_4 0x00FF22DD
#define IR_5 0x00FF02FD
#define IR_6 0x00FFC23D
#define IR_7 0x00FFE01F
#define IR_8 0x00FFA857
#define IR_9 0x00FF906F
#define IR_0 0x00FF9867
#define IR_A 0x00FF6897
#define IR_P 0x00FFB04F
#define IR_U 0x00FF18E7
#define IR_D 0x00FF4AB5
#define IR_L 0x00FF10EF
#define IR_R 0x00FF5AA5
#define IR_O 0x00FF38C7

// IRrecv object
IRrecv IR(irPin);
decode_results IRresults;

// loads the tone library, needed for 
TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);

// defaults for alarm time
String alarm1 = "";
String alarm2 = "";
String alarm3 = "";
String alarm4 = "";
String alarm = "00:00";
boolean alarmSet = false;

// defaults for current time
String current1 = "";
String current2 = "";
String current3 = "";
String current4 = "";
String setCurrent = "00:00";
String current = "00:00";
boolean currentSet = false;
unsigned long timeAtCurrentSet = 0;
int dayAdjustment = 0;

// keeping track of setting the times
String which = "";                    // keeps track of which time to set
int valueSet = 0;                     // keeps track of which value was set
unsigned long msInSetCurrentTime = 0; // initial milliseconds in set current time

// keeping track of when the alarm should be ringing
boolean alarmTriggered = false;
boolean alarmSounding = false;

// keeps track of time for motor movement
unsigned long delayTill = 0;

void irTick() {
  if(IR.decode(&IRresults)) {
    if (IRresults.value==IR_1) {
      keyPressed("1");
    }
    else if (IRresults.value==IR_2) {
       keyPressed("2");
    }
    else if (IRresults.value==IR_3) {
       keyPressed("3");
    }
    else if (IRresults.value==IR_4) {
       keyPressed("4");
    }
    else if (IRresults.value==IR_5) {
       keyPressed("5");
    }
    else if (IRresults.value==IR_6) {
       keyPressed("6");
    }
    else if (IRresults.value==IR_7) {
       keyPressed("7");
    }
    else if (IRresults.value == IR_8) {
       keyPressed("8");
    }
    else if (IRresults.value == IR_9) {
       keyPressed("9");
    }
    else if (IRresults.value == IR_0) {
       keyPressed("0");
    }
    else if (IRresults.value == IR_A) {
       keyPressed("*");
    }
    else if (IRresults.value == IR_P) {
       keyPressed("#");
    }
    else if (IRresults.value == IR_U) {
       keyPressed("U");
    }
    else if (IRresults.value == IR_D) {
       keyPressed("D");
    }
    else if (IRresults.value == IR_L) {
       keyPressed("L");
    }
    else if (IRresults.value == IR_R) {
       keyPressed("R");
    }
    else if (IRresults.value == IR_O) {
       keyPressed("O");
    }
    IRresults.value = 0;
    IR.resume();
    }
}

// alarm tone functions
void startBeep() {
  tone1.tone (600);
  delay (100);
  tone1.noTone ();
}

void beep() {
  tone1.tone (220);
  delay (100);
  tone1.noTone ();
}

void doubleBeep() {
  tone1.tone (600);
  delay (100);
  tone1.noTone ();
  delay (50);
  tone1.tone (600);
  delay (100);
  tone1.noTone ();
}

void keyPressed(String key) {

  // set alarm time
  if (key == "*") {
    which = "alarm";
    valueSet = 0;
    Serial.println("Now setting alarm...");
    startBeep();
  }
  else if (key == "#") {
    which = "current";
    valueSet = 0;
    Serial.println("Now setting current time...");
    startBeep();
  }
  else {
    if (valueSet == 0 && which == "alarm") {
      alarm1 = key;
      valueSet = 1;
      Serial.println(key);
      beep();
    }
    else if (valueSet == 1 && which == "alarm") {
      alarm2 = key;
      valueSet = 2;
      Serial.println(key);
      beep();
    }
    else if (valueSet == 2 && which == "alarm") {
      alarm3 = key;
      valueSet = 3;
      Serial.println(key);
      beep();
    }
    else if (valueSet == 3 && which == "alarm") {
      alarm4 = key;
      valueSet = 0;
      which = "";
      Serial.println(key);
      beep();
      alarm = alarm1 + alarm2 + ":" + alarm3 + alarm4;
      Serial.println("Alarm set to: " + alarm);
      alarmSet = true;
      doubleBeep();
    }
    else if (valueSet == 0 && which == "current") {
      current1 = key;
      valueSet = 1;
      Serial.println(key);
      beep();
    }
    else if (valueSet == 1 && which == "current") {
      current2 = key;
      valueSet = 2;
      Serial.println(key);
      beep();
    }
    else if (valueSet == 2 && which == "current") {
      current3 = key;
      valueSet = 3;
      Serial.println(key);
      beep();
    }
    else if (valueSet == 3 && which == "current") {
      current4 = key;
      valueSet = 0;
      which = "";
      Serial.println(key);
      beep();
      setCurrent = current1 + current2 + ":" + current3 + current4;
      Serial.println("Current time set to: " + setCurrent);
      timeAtCurrentSet = millis();
      int c1 = current1.toInt();
      int c2 = current2.toInt();
      int c3 = current3.toInt();
      int c4 = current4.toInt();
      msInSetCurrentTime = c1*10*60*60*1000L + c2*60*60*1000L + c3*10*60*1000L + c4*60*1000L;
      doubleBeep();
      currentSet = true;
    }
    else if (key == "O") {
      Serial.println("Ok button pressed... printing info...");
      Serial.println("Current time is: " + setCurrent);
      Serial.println("Alarm time is: " + alarm);
      beep();
    }
  }
}

void alarmTick() {
    tone1.tone (600);
    alarmSounding = true;
    alarmTriggered = false;
}

// motor movement functions
void backward(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,HIGH);
  delayTill = millis() + t;
}

void forward(int t) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW);
  delayTill = millis() + t;
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
  delayTill = millis() + t;
}

void turnRight(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delayTill = millis() + t;
}

void setMotorSpeed(int lspeed,int rspeed) { 
  // speed is between 0 and 255
  analogWrite(ENA,lspeed);
  analogWrite(ENB,rspeed);   
}

// keeps track of passed time without using delay
boolean canContinue() {
  if (delayTill > millis()) {
    return false;
  }
  else {
    return true;
  }
}

void randomDrive() {
  
  // turn
  if (canContinue()) {
    int turnDuration = random(250, 1000);   // turn for between 1/4 and 1 seconds
    int turnDirection = random(0,2);        // random direction to turn in 
    if (turnDirection == 0) {
      turnLeft(turnDuration);
    } else {
      turnRight(turnDuration);
    }
  }

  //  drive
  if (canContinue()) {
    int driveDuration = random(500, 3000);  // drive durration between 1/2 and 3 seconds
    int driveDirection = random(0, 2);      // forward or backward direction
    if (driveDirection == 0) {
      forward(driveDuration);
    } else {
      backward(driveDuration);
    }
  } 
}

void setup() {
  Serial.begin(9600);

  // IR reciever setup
  pinMode(irPin, INPUT);  
  pinMode(buzzerPin, OUTPUT);  
  IR.enableIRIn();

  // sets pins for motors
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

  // gets the IR code
  irTick();

  // triggers the alarm
  if (alarmTriggered & !alarmSounding) {
    alarmTick();
  }

  // random driving if the alarm is sounding
  if (alarmSounding) {
    randomDrive();
  }
  
  // runs after the current and alarm times have been set at least once
  if (currentSet) {
    
    // ms since the program started
    unsigned long timeSinceStart = millis();

    // ms since current time was set
    unsigned long msPassedSinceSet = (timeSinceStart - timeAtCurrentSet);
    
    // current time in ms
    unsigned long msInCurrentTime = msInSetCurrentTime + msPassedSinceSet - dayAdjustment*86400000;

    // builds a string of the current time
    int h1 = msInCurrentTime/10/60/60/1000;
    int h2 = msInCurrentTime/60/60/1000 - h1*10;
    int m1 = (msInCurrentTime/60/1000 - (h1*10 + h2) * 60) / 10;
    int m2 = (msInCurrentTime/60/1000 - (h1*10 + h2) * 60) - m1*10;
    current = String(h1) + String(h2) + ":" + String(m1) + String(m2);

    // adjust down one day if the time has passed midnight
    if (msInCurrentTime >= 86400000) {
      dayAdjustment++;
    }

    // turn the alarm bolean on when needed
    if (alarmSet & currentSet & alarm == current & !alarmTriggered) {
      alarmTriggered = true;
    }
  }
}
