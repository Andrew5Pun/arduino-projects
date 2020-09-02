/* Andrew Pun
    April 9, 2020
*/

// include pitches to easily convert to notes.
#include "pitches.h"

// ====SETTING UP PINS====
// pins for buttons
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;

//pins for LEDs
const int led1 = 6;
const int led2 = 7;
const int led3 = 8;
const int led4 = 9;

//pin for buzzer
const int buzzer = 12;


// ====CONFIGURABLES====
// most of these can be modified in the DIFFICULTY SELECT if statement in the void loop()
int timesToWin; // declare size of Array to win (how long the largest sequence is)


int specifiedLives; // intialize number of lives
int initialInterval; // intial duration between lights
int subtractedInterval; // duration added to initial

int timeToPress; // how many milliseconds you get to press the button
int timeToHold = 3000; // how many milliseconds you get to hold the button

//====DEBOUNCE VARIABLES====
int reading; // saves previous button pressed
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 200;    // the debounce time; increase if the output flickers

// ====TIMERS====

unsigned long timer = 0; // timer for seeing when button is pressed
unsigned long displayTimer = 0; // timer for how long you are allowed to press button

// function to convert 1 - 4 to correct pins for LED
int colourToLed(int colour) {

  if (colour == 1)
    return led1;
  if (colour == 2)
    return led2;
  if (colour == 3)
    return led3;
  if (colour == 4)
    return led4;

  return 0;
}

// function to convert 1 - 4 to correct pins for button
int colourToButton(int colour) {

  if (colour == 1)
    return button1;
  if (colour == 2)
    return button2;
  if (colour == 3)
    return button3;
  if (colour == 4)
    return button4;

  return 0;
}

// function to convert colour to tone
int colourToTone(int colour) {

  if (colour == 1)
    return NOTE_C4;
  if (colour == 2)
    return NOTE_E4;
  if (colour == 3)
    return NOTE_G4;
  if (colour == 4)
    return NOTE_C5;

}

// functions for playing note and lighting up LED
void redLight(int interval) {

  tone(buzzer, colourToTone(1), interval); // plays buzzer
  digitalWrite(led1, HIGH); // turns on LED
  delay(interval);
  digitalWrite(led1, LOW);
  delay(interval / 2);

}

void yellowLight(int interval) {

  tone(buzzer,  colourToTone(2), interval); // plays buzzer
  digitalWrite(led2, HIGH); // turns on LED
  delay(interval);
  digitalWrite(led2, LOW);
  delay(interval / 2);

}

void greenLight(int interval) {

  tone(buzzer,  colourToTone(3), interval); // plays buzzer
  digitalWrite(led3, HIGH); // turns on LED
  delay(interval);
  digitalWrite(led3, LOW);
  delay(interval / 2);

}

void blueLight(int interval) {

  tone(buzzer, colourToTone(4), interval); // plays buzzer
  digitalWrite(led4, HIGH); // turns on LED
  delay(interval);
  digitalWrite(led4, LOW);
  delay(interval / 2);

}

// function to call light from int 1 to 4
void callLight(int i, int interval) {
  if (i == 1)
    redLight(interval);
  if (i == 2)
    yellowLight(interval);
  if (i == 3)
    greenLight(interval);
  if (i == 4)
    blueLight(interval);
}

// fill function to fill array with random integers from 1 - 4
void fillArray(int intArray[], int sizeOfArray) {

  for (int i = 0; i < sizeOfArray; i++)
    intArray[i] = random(1, 5); // sets item to random number from 1 (inclusive) to 5 (exclusive)

}


int inputNewButton() { // function returns button that was pressed. If no button was pressed then it returns 0.

  // to prevent debounce, if a button is pressed twice the function checks if enough time has passed. Different buttons can be pressed with no delay between them, however.

  if (digitalRead(button1) == 0) {

    if ((millis() - lastDebounceTime) > debounceDelay || reading != 1)
      return 1;
    else
      lastDebounceTime = millis();  // reset the debouncing timer
      Serial.println("You're pressing too fast");
      
  }

  if (digitalRead(button2) == 0) {

    if ((millis() - lastDebounceTime) > debounceDelay || reading != 2)
      return 2;
    else
      lastDebounceTime = millis();  // reset the debouncing timer
      Serial.println("You're pressing too fast");
  }

  if (digitalRead(button3) == 0) {

    if ((millis() - lastDebounceTime) > debounceDelay || reading != 3)
      return 3;
    else
      lastDebounceTime = millis();  // reset the debouncing timer after a button has been pressed
      Serial.println("You're pressing too fast");
  }

  if (digitalRead(button4) == 0) {

    if ((millis() - lastDebounceTime) > debounceDelay || reading != 4)
      return 4;
    else
      lastDebounceTime = millis();  // reset the debouncing timer after a button has been pressed
      Serial.println("You're pressing too fast");

  }

  return 0;
}


// function for playing tone and LED sequence when winning game
void winTone() {
  Serial.println("You won!");
  int note = 400;
  digitalWrite(led4, HIGH);
  tone(buzzer, NOTE_C5, note * 1 / 3 * 3 / 4);
  delay(note * 1 / 3 * 2 / 3);
  digitalWrite(led4, LOW);
  delay(note * 1 / 3 * 1 / 3);
  digitalWrite(led4, HIGH);
  tone(buzzer, NOTE_C5, note * 1 / 3 * 3 / 4);
  delay(note * 1 / 3 * 2 / 3);
  digitalWrite(led4, LOW);
  delay(note * 1 / 3 * 1 / 3);
  digitalWrite(led4, HIGH);
  tone(buzzer, NOTE_C5, note * 1 / 3 * 3 / 4);
  delay(note * 1 / 3 * 2 / 3);
  digitalWrite(led4, LOW);
  delay(note * 1 / 3 * 1 / 3);
  digitalWrite(led4, HIGH);
  tone(buzzer, NOTE_C5, note * 3 / 4);
  delay(note * 2 / 3);
  digitalWrite(led4, LOW);
  delay(note * 1 / 3);
  digitalWrite(led1, HIGH);
  tone(buzzer, NOTE_GS4, note * 3 / 4);
  delay(note * 2 / 3);
  digitalWrite(led1, LOW);
  delay(note * 1 / 3);
  digitalWrite(led3, HIGH);
  tone(buzzer, NOTE_AS4, note * 3 / 4);
  delay(note * 2 / 3);
  digitalWrite(led3, LOW);
  delay(note * 1 / 3);
  digitalWrite(led4, HIGH);
  tone(buzzer, NOTE_C5, note * 3 / 4 * 3 / 4);
  delay(note * 3 / 4 * 2 / 3);
  digitalWrite(led4, LOW);
  delay(note * 3 / 4 * 1 / 3);
  digitalWrite(led3, HIGH);
  tone(buzzer, NOTE_AS4, note * 1 / 4 * 3 / 4);
  delay(note * 1 / 4 * 2 / 3);
  digitalWrite(led3, LOW);
  delay(note * 1 / 4 * 1 / 3);
  digitalWrite(led4, HIGH);
  tone(buzzer, NOTE_C5, note * 3 / 4);
  delay(note * 2 * 2 / 3);
  digitalWrite(led4, LOW);
  delay(note * 2 * 1 / 3);

}

// function for playing tone and LED lights when losing life. Shows which was correct light.
void loseLives(int lives, int correct) {

  int note = 200; // interval of time

  for (int i = 0; i < 3; i++) { // blink last LED and play sound

    digitalWrite(colourToLed(correct), HIGH);
    tone(buzzer, NOTE_F2, note * 3 / 4);
    delay(note * 2 * 2 / 3);
    digitalWrite(colourToLed(correct), LOW);
    delay(note * 2 * 1 / 3);

  }

}

// function for playing tone and LED lights when losing game
void loseTone() {

  Serial.println("You lost!");
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(buzzer, NOTE_A3, 500);
  delay(500);
  digitalWrite(led4, LOW);
  tone(buzzer, NOTE_GS3, 500);
  delay(500);
  digitalWrite(led3, LOW);
  tone(buzzer, NOTE_G3, 500);
  delay(500);
  digitalWrite(led2, LOW);
  tone(buzzer, NOTE_FS3, 500);
  delay(500);
  digitalWrite(led1, LOW);

}

void setup() { // set up all the input and output pins as well as the serial monitor
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(buzzer, OUTPUT);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {

  int gameCondition = 0; // int where 0 means the player is still playing, 1 means player has won, -1 means player has lost
  int rounds; // number of rounds played (in one game. Rounds go up to timesToWin)

  int interval; // time duration between lights

  int lives = specifiedLives; // reset to specified lives

  int pushedButton = 0; // integer denoting what button has been pressed from 1-4. 0 means no button was pressed.
  boolean buttonPressed = false;

  // ====DIFFICULTY SELECT====
  while (pushedButton == 0) { // loop until a button is pressed

    pushedButton = inputNewButton(); // see if a button is pressed

    // blinking pattern which runs in the background
    digitalWrite(colourToLed((millis() / 100) % 4 + 1), HIGH);
    digitalWrite(colourToLed((millis() / 100 + 1) % 4 + 1), LOW);
    digitalWrite(colourToLed((millis() / 100 + 2) % 4 + 1), LOW);
    digitalWrite(colourToLed((millis() / 100 + 3) % 4 + 1), LOW);

  }
  
  // turn off all LEDs
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  callLight(pushedButton, 200); // call the appropriate light with a hardcoded delay of 200 ms

  if (pushedButton == 1) { // Beginner
    lives = 3; // You get 3 lives
    initialInterval = 180; // The minimum delay between displayed lights is 180 ms
    subtractedInterval = 300; // The maximum delay between displayed lights is 180+300=480 ms which gets faster the longer the pattern is
    timesToWin = 5; // You play up to a pattern length of 5
    timeToPress = 4000; // You get 4 seconds to press a button
    rounds = 0; // you start at a 0+1=1 light long pattern
  }

  if (pushedButton == 2) { // Intermediate
    lives = 3; // You get 2 lives
    initialInterval = 180; // The minimum delay between displayed lights is 180 ms
    subtractedInterval = 260; // The maximum delay between displayed lights is 180+260=440 ms which gets faster the longer the pattern is
    timesToWin = 9; // You play up to a pattern length of 5
    timeToPress = 4000; // You get 4 seconds to press a button
    rounds = 0; // you start at a 0+1=1 light long pattern
  }

  if (pushedButton == 3) { // Advanced
    lives = 2;  // You get 2 lives
    initialInterval = 140; // The minimum delay between displayed lights is 140 ms
    subtractedInterval = 180; // The maximum delay between displayed lights is 140+180=320 ms which gets faster the longer the pattern is
    timesToWin = 11; // You play up to a pattern length of 11
    timeToPress = 3000; // You get 3 seconds to press a button
    rounds = 2; // you start at a 2+1=3 light long pattern
  }

  if (pushedButton == 4) { // Expert
    lives = 1; // You get 1 life
    initialInterval = 140; // The minimum delay between displayed lights is 140 ms
    subtractedInterval = 100; // The maximum delay between displayed lights is 140+100=240 ms which gets faster the longer the pattern is
    timesToWin = 15; // You play up to a pattern length of 15
    timeToPress = 2000; // You get 2 seconds to press a button
    rounds = 4; // you start at a 4+1=5 light long pattern

  }

  int colourArray[timesToWin]; // declare colourArray
  delay(1000);



  //====GAME STARTS====

  fillArray(colourArray, timesToWin); // start by filling colourArray with random nubmers from 1 to 4

  while (gameCondition == 0 && lives > 0) { // loop while gameCondition = 0 and player still has lives
    reading = 0; // reset reading to 0
    
    Serial.print("Round: ");
    Serial.print(rounds + 1);
    Serial.print(" of ");
    Serial.println(timesToWin);

    interval = initialInterval + max(0, subtractedInterval - 20 * rounds); // change interval to make it faster each time. Minimum interval is initialInterval

    for (int i = 0; i <= rounds; i++) { // loop to display sequence
      callLight(colourArray[i], interval);
    }

    int counter = 0;

    while (counter <= rounds && gameCondition == 0) { // loop for playing sequence
      timer = millis(); // set timer
      pushedButton = 0; // reset correctButton to 0
      buttonPressed = false; // reset buttonPressed to false

      // you have a few seconds to press a button or you lose
      while ((millis() - timer) <= timeToPress && pushedButton == 0) { // loop until time has been exceeded or button is pressed

        pushedButton = inputNewButton(); // see if button is pressed
        
      }

      reading = pushedButton; // set reading to previous pushed button

      lastDebounceTime = millis();  // reset the debouncing timer after a button has been pressed
      
      Serial.print("You pressed: ");
      Serial.println(pushedButton);
      

      if (pushedButton != colourArray[counter]) { // if losing condition is met
        if (pushedButton == 0) {
          Serial.println("You ran out of time");
        } else {
          Serial.print("The correct button is ");
          Serial.println(colourArray[counter]);
          
        }

        lives --; // player loses life
        loseLives(lives, colourArray[counter]);
        gameCondition = -1;
        Serial.print("You lost 1 life. You have ");
        Serial.print(lives);
        Serial.println(" left");

      }

      displayTimer = millis(); // set display timer
      while (pushedButton == colourArray[counter] && (millis() - displayTimer <= timeToHold) && digitalRead(colourToButton(colourArray[counter])) == 0) { // loop to play buzzer and light until button is not held or time is up
        tone(buzzer, colourToTone(colourArray[counter])); // plays buzzer

        digitalWrite(colourToLed(colourArray[counter]), HIGH); // turns on LED
      }
      
      noTone(buzzer); // turn off buzzer
      digitalWrite(colourToLed(colourArray[counter]), LOW); // turn off the LED

      if (gameCondition == 0) {
        counter++; // increase the pattern length by 1
      }

    }

    if (gameCondition == 0) {

      rounds++; // increase rounds by 1
    }

    if (rounds >= timesToWin) {

      gameCondition = 1; // if you passed all the rounds then you win

    } else {

      gameCondition = 0; // if there are still rounds left the game keeps going

    }

    if (lives > 0 && gameCondition <= 0) { // delay for 1 second only if player is still playing game
      delay(1000);
    }


  }

  if (lives <= 0) // if you have no more lives then you lose
    loseTone();
  else // if you still have lives you win
    winTone();

  
  //====END OF GAME====
  delay(1000);

}
