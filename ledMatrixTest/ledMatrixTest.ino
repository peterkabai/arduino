#include <MatrixLED.h>

// the WeMos pns that need to be connected are:
// 5v, 3v, D5, and D7

MLED mled(5); // set the intensity to 5
int LEDs = 8;

void setup() {   
  // no setup code needed
}

void loop() {   
  // for each row of LEDs
  for(int y=0; y<LEDs; y++){  
    // for each column of LEDs
    for(int x=0; x<LEDs; x++){   

      mled.dot(x,y);   // draw dot      
      mled.display();  // display dot
      delay(200);      
      mled.dot(x,y,0); // clear dot     
      mled.display();
      delay(200);
     }
   } 
}
