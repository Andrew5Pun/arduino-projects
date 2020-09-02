  /* Andrew Pun
   *  March 16, 2020
   */
  
  
  // initialize all the pins
  int ledPin1 = 8;
  int ledPin2 = 9;
  int ledPin3 = 10;
  int ledPin4 = 11;
  int pin = 0; // variable pin that starts at 8 (ledPin1)

void setup() {
  // setup all pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  
}

void loop() {

  digitalWrite((pin % 4 + 8), HIGH); // turn on LED at pin
  delay(1000); // wait 1 second
  digitalWrite((pin % 4 + 8), LOW); // turn off LED at pin
  pin ++; // add 1 to pin

}
