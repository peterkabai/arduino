#include <EEPROM.h>

struct VarObject {
  String one;
  String two;
};

// clears EEPROM 
void clearMemory() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void setup() {
  Serial.begin(9600);

  // clears EEPROM 
  clearMemory();
  
  // create a float, store it
  float f = 123.456f;
  EEPROM.put(0, f);

  // read back the float, print
  float valueOutput;
  EEPROM.get(0, valueOutput);
  Serial.println(valueOutput);

  // create an object, store it
  VarObject custom = {
    "Hello",
    "World"
  };
  EEPROM.put(1, custom);

  // read back the object, print
  VarObject customVar;
  EEPROM.get(1, customVar);
  Serial.println(customVar.one);
  Serial.println(customVar.two);
  
}

void loop() {
  
}
