#ifndef _OLED_DISPAY_H
#define _OLED_DISPAY_H
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>
#include <SPI.h>
#include <Wire.h>
#include "Arduino.h"
#include <cppQueue.h>
#include <Vector.h>


#define WHITE SH110X_WHITE
#define BLACK SH110X_BLACK

// #define WHITE SSD1306_WHITE
// #define BLACK SSD1306_BLACK

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C

extern Adafruit_SH1106G myScreen;
//extern Adafruit_SSD1306 myScreen;

typedef struct{
  int X;
  int Y;
}Head;

typedef struct{
  int X;
  int Y;
}Tail;

typedef struct{
  int X;
  int Y;
}Bait;

typedef enum{
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT
}SnakeDir;

typedef struct{
  uint8_t X;
  uint8_t Y;
}SnakeStep;

extern cppQueue q;
extern Vector<SnakeStep> step;

void logo();
void initSystem();
void randomBait(bool flag);
bool snakeRun();
void score();
void gameOver(SnakeDir dir);
#endif