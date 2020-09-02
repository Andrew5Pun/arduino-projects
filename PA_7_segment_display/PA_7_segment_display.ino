/* Andrew Pun
    April 25, 2020
*/

// ====SETTING UP PINS====

int del = 700; // adjust delay between characters

// pins for segments and decimal
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;
const int dp = 9;

String myString = ""; // string for input

// array was taken from https://en.wikichip.org/wiki/seven-segment_display/representing_letters but modified so that some other characters exist
const unsigned char abcdefg[75] = { // array containing hex characters. Some are missing since they can't be displayed with 7 segments
  /*  0     1     2     3     4     5     6     7     8     9     :     ;     */
  0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x00, 0x00,
  /*  <     =     >     ?     @     A     B     C     D     E     F     G     */
  0x00, 0x09, 0x00, 0x00, 0x00, 0x77, 0x00, 0x4E, 0x3D, 0x4F, 0x47, 0x5E,
  /*  H     I     J     K     L     M     N     O     P     Q     R     S     */
  0x37, 0x06, 0x3C, 0x00, 0x0E, 0x00, 0x15, 0x7E, 0x67, 0x73, 0x05, 0x5B,
  /*  T     U     V     W     X     Y     Z     [     \     ]     ^     _     */
  0x0F, 0x3E, 0x00, 0x00, 0x00, 0x3B, 0x6D, 0x00, 0x00, 0x00, 0x08, 0x00,
  /*  `     a     b     c     d     e     f     g     h     i     j     k     */
  0x00, 0x7D, 0x1F, 0x0D, 0x3D, 0x4F, 0x47, 0x5E, 0x17, 0x10, 0x3C, 0x00,
  /*  l     m     n     o     p     q     r     s     t     u     v     w     */
  0x0E, 0x00, 0x15, 0x1D, 0x67, 0x73, 0x05, 0x5B, 0x0F, 0x1C, 0x00, 0x00,
  /*  x     y     z     */
  0x00, 0x3B, 0x6D
};


void writeAllLow() { // function to write all segments as low

  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, LOW);

}

void decodeSegment(char dis) { // function that reads input and lights up segments
  // basically decodes dis to binary and lights up specified segments

  digitalWrite(g, dis % 2 == 1);
  dis /= 2;
  digitalWrite(f, dis % 2 == 1);
  dis /= 2;
  digitalWrite(e, dis % 2 == 1);
  dis /= 2;
  digitalWrite(d, dis % 2 == 1);
  dis /= 2;
  digitalWrite(c, dis % 2 == 1);
  dis /= 2;
  digitalWrite(b, dis % 2 == 1);
  dis /= 2;
  digitalWrite(a, dis % 2 == 1);
  digitalWrite(dp, LOW);
}

void segmentDisplay(int pos) { // function that takes in int pos and converts to instructions for 7 seg display
  writeAllLow();

  if (pos >= 0 && pos < 75) { // check if dis is within 0 - 75.
    decodeSegment(abcdefg[pos]); // decode and display the character found in the abcdefg array at posdi
  } else {
    if (pos == -2) { // hardcoded part that writes to pin dp to do char '.'
      digitalWrite(dp, HIGH); // write dp as high
    }
  }

}

void displayMsg(String message) { // function for displaying message

  Serial.println("Your message was: " + message);

  for (int i = 0; i < message.length() - 1; i++) { // loop through the string -1 to avoid new line
    segmentDisplay((int)(message.charAt(i) - 48)); // print the individual character
    delay(del); // wait
    writeAllLow(); // turn off all segments briefly
    delay(100);
  }

}

void setup() {
  // set up serial monitor and pins
  Serial.begin(9600);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

}

void loop() {

  Serial.println("Type in your message (some letters may not be supported): ");

  while (!Serial.available()) { // wait until serial is available
  }

  while (Serial.available()) { // loop while serial is available
    char c = Serial.read(); // read one char at a time
    myString += c; // add char to myString
    delay(2);
  }
  if (myString != "") { // if string is not empty

    displayMsg(myString); // display message
  }
  myString = ""; // reset string to be empty

}
