  /* Andrew Pun
   *  March 16, 2020
   *  Exercise 1.2
   */
  
  
  // initialize all the pins
  int ledPin1 = 8;
  int ledPin2 = 9;
  int ledPin3 = 10;
  int ledPin4 = 11;
  int pin = ledPin1; // variable pin that starts at 8 (ledPin1)

void setup() {
  // setup all pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  
}

void loop() {
  while (pin <= ledPin4) { // loop until pin is greater than 11 (ledPin4)
    digitalWrite(pin, HIGH); // turn on LED at pin
    delay(1000); // wait 1 second
    pin ++; // add 1 to pin
  }
  pin = ledPin4; // set pin to 11
  while (pin >= ledPin1) { // loop until pin is less than 8 (ledPin1)
    
    digitalWrite(pin, LOW); // turn off LED at pin
    delay(1000); // wait 1 second
    pin --; // subtract 1 from pin
  }
  pin = ledPin1; // set pin back to 8
}
