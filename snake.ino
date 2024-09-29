#include "oled_display.h"
#include <cppQueue.h>
#include <Vector.h>


extern SnakeDir snakeDir;
extern bool gameOverFlag;

//Adafruit_SSD1306 myScreen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SH1106G myScreen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
cppQueue	q(sizeof(SnakeDir), 30, FIFO);	
Vector<SnakeStep> step;

void setup() {
  //Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  logo();
  randomSeed(analogRead(0) + analogRead(1));
  delay(1000);
  myScreen.clearDisplay();
  myScreen.display();
  initSystem();
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButton();
  randomBait(false);
  if(!snakeRun())
    gameOver(snakeDir);
  score();
}

void checkButton(){
  if(gameOverFlag){
    if(digitalRead(4) == 0 || digitalRead(5) == 0 || digitalRead(6) == 0 || digitalRead(7) == 0)
      snakeDir = MOVE_UP;
      return;
  }
  if(digitalRead(4) == 0 && snakeDir != MOVE_DOWN && snakeDir != MOVE_UP){
    snakeDir = MOVE_UP;
    return;
  }
  if(digitalRead(6) == 0 && snakeDir != MOVE_UP && snakeDir != MOVE_DOWN){
    snakeDir = MOVE_DOWN;
    return;
  }
  if(digitalRead(7) == 0 && snakeDir != MOVE_RIGHT && snakeDir != MOVE_LEFT){
    snakeDir = MOVE_LEFT;
    return;
  }
  if(digitalRead(5) == 0 && snakeDir != MOVE_LEFT && snakeDir != MOVE_RIGHT){
    snakeDir = MOVE_RIGHT;
    return;
  }
}





