int input;
String output = "";

// converts input decimal to a string
String convertToLetter(int input) {
  switch (input) {
    case 49:
        return "a";
    case 50:
        return "b";
    case 51:
        return "c";
    case 52:
        return "d";
    case 53:
        return "e";
    case 54:
        return "f";
    case 55:
        return "g";
    case 56:
        return "h";
    case 57:
        return "i";
    case 58:
        return "j";
    case 59:
        return "k";
    case 60:
        return "l";
    case 61:
        return "m";
    case 62:
        return "n";
    case 63:
        return "o";
    case 64:
        return "p";
    case 65:
        return "q";
    case 66:
        return "r";
    case 67:
        return "s";
    case 68:
        return "t";
    case 69:
        return "u";
    case 70:
        return "v";
    case 71:
        return "w";
    case 72:
        return "x";
    case 73:
        return "y";
    case 74:
        return "z";
    case 17:
        return "A";
    case 18:
        return "B";
    case 19:
        return "C";
    case 20:
        return "D";
    case 21:
        return "E";
    case 22:
        return "F";
    case 23:
        return "G";
    case 24:
        return "H";
    case 25:
        return "I";
    case 26:
        return "J";
    case 27:
        return "K";
    case 28:
        return "L";
    case 29:
        return "M";
    case 30:
        return "N";
    case 31:
        return "O";
    case 32:
        return "P";
    case 33:
        return "Q";
    case 34:
        return "R";
    case 35:
        return "S";
    case 36:
        return "T";
    case 37:
        return "U";
    case 38:
        return "V";
    case 39:
        return "W";
    case 40:
        return "X";
    case 41:
        return "Y";
    case 42:
        return "Z";
    case -15:
        return "!";
    case -4:
        return ",";
    case 16:
        return "@";
    case -13:
        return "#";
    case -12:
        return "$";
    case -11:
        return "%";
    case -16:
        return " ";
    default: 
      Serial.println("Char " + String(input) + " not set up"); 
      return "";
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {

  // if there is serial input
  if (Serial.available() > 0) {

    // reads and zeros out the input
    input = Serial.read();
    input = input - 48;

    // if the string is not the end of the line
    if (String(input) != String(-38)) {  

      // if the int value is a number
      if (input < 10 && input > -1) {
        output = output+input;
      } 

      // convert the into to a letter
      else {
        output = output+convertToLetter(input);
      }
    }

    // print the string at the end of the line
    else {
      Serial.println(output);
      output = "";
    }
  }
}
