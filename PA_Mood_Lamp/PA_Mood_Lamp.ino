/* Andrew Pun
    April 17, 2020
*/


// include pitches to easily convert to notes.
#include "pitches.h"

// debounce variables
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled for button 1
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled for button 2
unsigned long lastDebounceTime3 = 0;  // the last time the output pin was toggled for button 3

int buttonState1;             // the current reading from the input pin for button 1
int buttonState2;             // the current reading from the input pin for button 2
int buttonState3;             // the current reading from the input pin for button 3

int lastButtonState1 = LOW;   // the previous reading from the input pin for button 1
int lastButtonState2 = LOW;   // the previous reading from the input pin for button 2
int lastButtonState3 = LOW;   // the previous reading from the input pin for button 3

unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers

// variables for mode
int moodMode = 0; // mode to set mood. Goes from 0 to 3. Adjusted using button 1.
int speedMode = 5; // mode to set speed. Goes from 0 to 10. Starts at 5 and can be adjusted using button 2 and 3.
int brightMode = 0; // mode to set brightness. Based on potentiometer.

// pins for buttons
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;

// pin for piezo buzzer
const int buzzer = 5; // analog pin A5

// pin for potentiometer
const int potpin = 5;

// pins for RGB LED
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

void callTheme(int moodM, int speedM, int brightM) { // plays light and tone from speaker

  int speedVal = 1200 - speedM * 110; // set speedVal based on value of speedM. Min speedVal of 100 since max val of speedM is 10.
  
  if ((millis() % speedVal) == 0) { // only play note/change light when certain time has passed
    if (moodM == 0) { // christmas lights theme

      // play appropriate sound and light based on time
      if ((millis() / (speedVal/10)) % 3 == 0) {
        RGBWrite(255, 255, 255, brightM);
        tone(buzzer, NOTE_C4);
      }
      if ((millis() / (speedVal/10)) % 3 == 1) {
        RGBWrite(255, 0, 0, brightM);
        tone(buzzer, NOTE_E4);
      }
      if ((millis() / (speedVal/10)) % 3 == 2) {
        RGBWrite(0, 255, 0, brightM);
        tone(buzzer, NOTE_G4);
      }
        
    }
    if (moodM == 1) { // warm colour theme

      // play appropriate sound and light based on time
      if ((millis() / (speedVal/10)) % 3 == 0) {
        RGBWrite(204, 30, 0, brightM);
        tone(buzzer, NOTE_CS4);
      }
      if ((millis() / (speedVal/10)) % 3 == 1) {
        RGBWrite(244, 0, 3, brightM);
        tone(buzzer, NOTE_B3);
      }
      if ((millis() / (speedVal/10)) % 3 == 2) {
        RGBWrite(255, 100, 0, brightM);
        tone(buzzer, NOTE_F4);
      }
        
    }

    if (moodM == 2) { // cool colour theme

      // play appropriate sound and light based on time
      if ((millis() / (speedVal/10)) % 3 == 0) {
        RGBWrite(86, 255, 255, brightM);
        tone(buzzer, NOTE_F5);
      }
      if ((millis() / (speedVal/10)) % 3 == 1) {
        RGBWrite(0, 0, 255, brightM);
        tone(buzzer, NOTE_A4);
      }
      if ((millis() / (speedVal/10)) % 3 == 2) {
        RGBWrite(153, 51, 255, brightM);
        tone(buzzer, NOTE_D5);
      }
    }
    
    if (moodM == 3) { // random theme
      tone(buzzer, random(700, 3000)); // play randome tone
      RGBWrite(random(1, 254), random(1, 254), random(1, 254), brightM); // make random colour
    }
    
  }
}

void RGBWrite (int r, int g, int b, int brightness) { // function to easily write to RGB LED
  Serial.println(brightness);
  // cap r g b values at 255. Since it is a common anode, r g b values determined by subtracting from 255. r g b values are multiplied by the brightness.
  r = min(255, 255 - r*(min(1.0, (brightness-2)/1023.0)));
  g = min(255, 255 - g*(min(1.0, (brightness-2)/1023.0)));
  b = min(255, 255 - b*(min(1.0, (brightness-2)/1023.0)));

  // write to the actual pins with the r g b values
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);

}


void setup() { // set up all input and output pins and serial monitor and randomSeed

  Serial.begin(9600);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzer, OUTPUT);


  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {
  
  // read state of the buttons into local variable
  int reading1 = digitalRead(button1);
  int reading2 = digitalRead(button2);
  int reading3 = digitalRead(button3);



  if (reading1 != lastButtonState1) { // If the switch changed, due to noise or pressing
    lastDebounceTime1 = millis();  // reset the debouncing timer for button 1
  }
  if (reading2 != lastButtonState2) { // If the switch changed, due to noise or pressing
    lastDebounceTime2 = millis();  // reset the debouncing timer for button 2
  }
  if (reading3 != lastButtonState3) { // If the switch changed, due to noise or pressing
    lastDebounceTime3 = millis();  // reset the debouncing timer for button 3
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) { // button 1 responsible for changing theme

    if (reading1 != buttonState1) { // if the button state has changed
      buttonState1 = reading1;

      if (buttonState1 == LOW) {
        
        moodMode = (1 + moodMode) % 4; // increment moodMode by 1 but wrap around to 0 when it equals 4. moodMode can only have values 0 to 3.
        Serial.print("moodMode: ");
        Serial.println(moodMode);
      }
    }

  }

  if ((millis() - lastDebounceTime2) > debounceDelay) { // button 2 responsible for decreasing speed

    if (reading2 != buttonState2) { // if the button state has changed
      buttonState2 = reading2;

      if (buttonState2 == LOW) {
        
        speedMode = max(0, speedMode - 1); // increment speedMode by -1 and make lower bound 0. Cannot go past 0.
        Serial.print("speedMode: ");
        Serial.println(speedMode);
      }
    }
  }

  if ((millis() - lastDebounceTime3) > debounceDelay) { // button 3 responsible for increasing speed

    if (reading3 != buttonState3) { // if the button state has changed
      buttonState3 = reading3;

      if (buttonState3 == LOW) {
        
        speedMode = min((1 + speedMode), 10); // increment speedMode by 1 and cap it at 10. Cannot go past 10.
        Serial.print("speedMode ");
        Serial.println(speedMode);
      }
    }
  }

  brightMode = analogRead(potpin); // set speedMode to value of potentiometer, divided by 102
  //Serial.println(brightMode);
  
  // call tone and light
  callTheme(moodMode, speedMode, brightMode);
  

  // save all of the buttons' readings
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
}
