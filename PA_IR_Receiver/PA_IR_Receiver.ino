/* Andrew Pun
    April 28, 2020
*/

#include <IRremote.h> // import the IRremote library

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

// pin for IR sensor
const int IR = 11;

IRrecv irrecv(IR);

decode_results results;

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

const unsigned int codes[10] = {0xF796, 0xF731, 0xF78D, 0xF702, 0xF7C2, 0xF726, 0xF7C6, 0xF716, 0xF7E4, 0xF766}; // contains hexcodes for digits from 0 to 9 from the IR remote

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

  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

}

void loop() {

  if (irrecv.decode(&results)) //this checks to see if a code has been received
  {
    Serial.println(results.value, HEX); // display reading in serial monitor

    // display digits
    if (results.value == codes[1]) { // press 1
      decodeSegment(abcdefg[1]);
    }
    if (results.value == codes[2]) { // press 2
      decodeSegment(abcdefg[2]);
    }
    if (results.value == codes[3]) { // press 3
      decodeSegment(abcdefg[3]);
    }
    if (results.value == codes[4]) { // press 4
      decodeSegment(abcdefg[4]);
    }
    if (results.value == codes[5]) { // press 5
      decodeSegment(abcdefg[5]);
    }
    if (results.value == codes[6]) { // press 6
      decodeSegment(abcdefg[6]);
    }
    if (results.value == codes[7]) { // press 7
      decodeSegment(abcdefg[7]);
    }
    if (results.value == codes[8]) { // press 8
      decodeSegment(abcdefg[8]);
    }
    if (results.value == codes[9]) { // press 9
      decodeSegment(abcdefg[9]);
    }
    if (results.value == codes[0]) { // press 0
      decodeSegment(abcdefg[0]);
    }



    irrecv.resume(); // Receive the next value
    delay(300); // delay
  }

}
