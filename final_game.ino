//libs for cpx board
#include <Adafruit_CircuitPlayground.h>
//needed for internal communication, not called in my code
#include <Wire.h>
#include <SPI.h>

//global vars
int score = 0;
int strikes = 0;
int level = 1; //track player progression
int roundCount = 0;
int maxRounds = 15; //game over condt's 
int maxStrikes = 3; //game over condt's
unsigned long roundDuration = 3000; // 3 seconds to start, time for player to resp
bool lastSwitchState; //switch's prev position

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  lastSwitchState = CircuitPlayground.slideSwitch();
  introSequence();
}

//main game loop
void loop() {
  if (strikes >= maxStrikes || roundCount >= maxRounds) { //win/loss condt's
    endGame();
    return;
  }

  int color = random(3); // 0 = red, 1 = green, 2 = blue
  flashColor(color);
  bool correct = waitForInput(color);

  if (correct) {
    score++;
    CircuitPlayground.playTone(880, 200); // positive sound
  } else {
    strikes++;
    CircuitPlayground.playTone(200, 400); // wrong sound
  }

  roundCount++;
  if (score > 0 && score % 5 == 0) {
    level++;
    roundDuration = max(1000, roundDuration - 500); // speed up. score 5=2.5 sec, 10=2sec, 15=1.5 sec
  delay(500); // pause before next round
}

void introSequence() {
  CircuitPlayground.clearPixels(); //turn off prev lights
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 0); //light up all pixels yellow
  }
  delay(1000);
  CircuitPlayground.clearPixels(); //off to start game
}

void flashColor(int color) {
  CircuitPlayground.clearPixels();
  for (int i = 0; i < 10; i++) {
    if (color == 0) CircuitPlayground.setPixelColor(i, 255, 0, 0); // red
    else if (color == 1) CircuitPlayground.setPixelColor(i, 0, 255, 0); // green
    else CircuitPlayground.setPixelColor(i, 0, 0, 255); // blue
  }
}

bool waitForInput(int targetColor) { //true if react in time, else = false
  unsigned long startTime = millis(); //starts timer. starttime so i can see how much time has passed
  bool currentSwitchState = CircuitPlayground.slideSwitch();

  while (millis() - startTime < roundDuration) { //keep looping as long as the amt of time thats passed since start time is less than round duration
    if (targetColor == 0 && CircuitPlayground.leftButton()) return true;
    if (targetColor == 1 && CircuitPlayground.rightButton()) return true;
    if (targetColor == 2) {
      bool newSwitch = CircuitPlayground.slideSwitch(); //reads current switch position
      if (newSwitch != lastSwitchState) { //is current slide switch diff from prev one stored in lastSwitchState
        lastSwitchState = newSwitch; //update switch state to new position
        return true;
      }
    }
  }
  return false;
}

//once game over
void endGame() {
  CircuitPlayground.clearPixels();
  for (int i = 0; i < 10; i++) {
    if (score >= maxRounds) CircuitPlayground.setPixelColor(i, 0, 255, 255); // win color
    else CircuitPlayground.setPixelColor(i, 255, 0, 255); // game over color
  }
  CircuitPlayground.playTone(500, 1000);
  while (1); //freezes program
}
