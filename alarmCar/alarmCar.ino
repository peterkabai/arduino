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

// note definitions for tones
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// IRrecv object
IRrecv IR(irPin);
decode_results IRresults;

// mario themesong
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
int noteDurations[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

// starwars
int melodyStarwars[] = {
   NOTE_D3, NOTE_D3, NOTE_D3, NOTE_G3, 
   NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3, 
   NOTE_G4, NOTE_D4, NOTE_C4, NOTE_B3, 
   NOTE_A3, NOTE_G4, NOTE_D4, NOTE_C4, 
   NOTE_B3, NOTE_C4, NOTE_A3 
};
int noteDurationsStarwars[] = {
  6, 6, 6, 2, 
  2, 6, 6, 6, 
  2, 2, 6, 6, 
  6, 2, 2, 6, 
  6, 6, 1
};

// annoying tone
int melodyAnnoying[] = { 
  NOTE_D3, NOTE_AS3, NOTE_FS4, NOTE_D5, NOTE_AS5, NOTE_FS6,
  NOTE_D3, NOTE_AS3, NOTE_FS4, NOTE_D5, NOTE_AS5, NOTE_FS6,
  NOTE_D3, NOTE_AS3, NOTE_FS4, NOTE_D5, NOTE_AS5, NOTE_FS6,
  NOTE_D3, NOTE_AS3, NOTE_FS4, NOTE_D5, NOTE_AS5, NOTE_FS6,
  NOTE_D3, NOTE_AS3, NOTE_FS4, NOTE_D5, NOTE_AS5, NOTE_FS6,
  NOTE_D3, NOTE_AS3, NOTE_FS4, NOTE_D5, NOTE_AS5, NOTE_FS6,
  NOTE_D3, NOTE_AS3, NOTE_FS4, NOTE_D5, NOTE_AS5, NOTE_FS6,
};
int noteDurationsAnnoying[] = {
  2, 2, 2, 2, 2, 2,
  4, 4, 4, 4, 4, 4,
  8, 8, 8, 8, 8, 8,
  4, 4, 4, 4, 4, 4,
  2, 2, 2, 2, 2, 2
};

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
unsigned long oneMinPastAlarm = 0;

// keeps track of time for motor movement
unsigned long delayTill = 0;
boolean lastActionTurn = false;

// keeps track of time for the tone delay
unsigned long delayTillNextTone = 0;
boolean needsPause = false;

// needed for looping through the noted in the melody
int thisNote = 0;
int lengthOfMelody = sizeof(noteDurations) / 2;

// plays the next note of the melody, if canPlay is true
void continueMelody() {
  int noteDuration = 1000 / noteDurations[thisNote];
  if (canPlay() && !needsPause) {
    // the length of the note is 1 second divided by the note type
    if (melody[thisNote] != 0) {
      tone1.tone(melody[thisNote]);
    } else {
      tone1.noTone();
    }
    delayTillNextTone = millis() + noteDuration;
    needsPause = true;
    // 30% pasue between notes
  } else if (canPlay() && needsPause) {
    tone1.noTone();
    int pauseBetweenNotes = noteDuration * 0.30;
    delayTillNextTone = millis() + pauseBetweenNotes;
    needsPause = false;
    ++thisNote;
    if (thisNote == lengthOfMelody) {
      thisNote = 0;
    }
  }
}

// keeps track of passed time without using delay
boolean canPlay() {
  if (delayTillNextTone > millis()) {
    return false;
  } else {
    tone1.noTone();
    return true;
  }
}

// runs every loop to check for IR remote input
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
      oneMinPastAlarm = 0;
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
      currentSet = true;
      oneMinPastAlarm = 0;
      doubleBeep();
    }
    else if (key == "O") {
      tone1.noTone();
      alarmTriggered = false;
      stopMotor();
    }
  }
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
  if (canContinue() & !lastActionTurn) {
    int turnDuration = random(250, 1000);   // turn for between 1/4 and 1 seconds
    int turnDirection = random(0,2);        // random direction to turn in 
    if (turnDirection == 0) {
      turnLeft(turnDuration);
    } else {
      turnRight(turnDuration);
    }
    lastActionTurn = true;
  }

  //  drive
  else if (canContinue()) {
    int driveDuration = random(500, 3000);  // drive durration between 1/2 and 3 seconds
    int driveDirection = random(0, 2);      // forward or backward direction
    if (driveDirection == 0) {
      forward(driveDuration);
    } else {
      backward(driveDuration);
    }
    lastActionTurn = false;
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

  // triggers the alarm melody
  if (alarmTriggered) {
    continueMelody();
  } else { // resets the melody if the alarm is off
    thisNote = 0;
  }

  // random driving if the alarm is sounding
  if (alarmTriggered) {
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
    if (alarmSet & currentSet & alarm == current & !alarmTriggered & (millis() > oneMinPastAlarm) ) {
      oneMinPastAlarm = millis() + 60000;
      alarmTriggered = true;
    }
  }
}
