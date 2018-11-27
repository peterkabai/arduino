#include <IRremote.h>

int pin = 4;
IRrecv irrecv(pin);
decode_results signals;

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&signals)) {
  Serial.println(signals.value, HEX);
  irrecv.resume();
  }
}
