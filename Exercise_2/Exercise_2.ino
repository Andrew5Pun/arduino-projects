  /* Andrew Pun
   *  March 16, 2020
   *  Exercise 2.2
   */
  
  
  // initialize all the pins in a pin array
  int ledPins[4] = {5, 6, 9, 10};
  int pin = 0; // variable pin that starts at 0

void setup() {
  // setup all pins as outputs
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  pinMode(ledPins[3], OUTPUT);
  
}

void loop() {
  analogWrite(ledPins[pin % 4], pin*5+1); // turn on LED at specified pin in array and give analog output of pin*5+1
  delay(500); // wait 1/2 second
  analogWrite(ledPins[pin % 4], 0); // turn off LED at at specified pin in array
  pin ++; // add 1 to pin
  
}
