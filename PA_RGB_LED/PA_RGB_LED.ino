  /* Andrew Pun
   *  March 16, 2020
   *  Exercise 3
   */
  
  
  // initialize all the pins, red, green, and blue
  int red = 9;
  int green = 10;
  int blue = 11;

void setup() {
  // setup all pins as outputs
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
}

void loop() {
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);
  ///*
  for (int r = 0; r <= 255; r += 10) { // cycle through all values of red from 0 to 255 in steps of 10
    for (int g = 0; g <= 255; g += 10) { // cycle through all values of green from 0 to 255 in steps of 10
      for (int b = 0; b <= 255; b += 10) {// cycle through all values of blue from 0 to 255 in steps of 10
    
        // analog write to all colour pins with r, g, b values
        analogWrite(red, r);
        analogWrite(green, g);
        analogWrite(blue, b);
        delay(100); // wait 1/10 second
      }
    }
  }
  //*/
  
}
