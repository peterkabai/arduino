const int pin = 0; // WeMos pin D3
int pin_value = 1;
int odo = 0;
const int circ = 2136;
double km = 0.0;
int prev_time = 0;
float kmph = 0;
float km_per_revolution = circ / 1000.0 / 1000.0;
int refresh_rate = 1;
double km_per_mile = 1.609;
int prev_tick = 0;
int time_since = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
  delay(1000);
}

void loop() {
  int old_value = pin_value;
  pin_value = digitalRead(pin);
  if (pin_value == 0 && old_value == 1) {
    odo = odo + 1;
    km = km + km_per_revolution;
    time_since =  millis() - prev_tick;
    prev_tick = millis();
  }

  int current_time = millis();
  int time_passed = current_time - prev_time;
  
  if ( time_passed > refresh_rate * 1000) {
      if ((millis() - prev_tick) > 3000 || (time_since / 1000.0 / 60.0 / 60.0) == 0) {
        kmph = 0;
      } else {
        kmph = km_per_revolution / (time_since / 1000.0 / 60.0 / 60.0);
      }

      Serial.println(
        "Distance: " + String(km/km_per_mile) + 
        " miles - Speed: " + String(kmph/km_per_mile) + 
        " mph - Rotations: " + String(odo)
      );
      prev_time = millis();
  }
  
  delay(10);
}

