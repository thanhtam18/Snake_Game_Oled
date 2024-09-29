#include "oled_display.h"
#include "icon.h"

unsigned long intervalBait = 0;
unsigned long intervalSnake = 0;

SnakeStep stepArr[100];

int longSnake = 22;
bool gameOverFlag = false;

Head head = { 60, 24 };
Tail tail = { head.X + longSnake, 24 };
Bait bait;

uint16_t myScore = 0;

SnakeDir snakeDir = MOVE_LEFT;

void logo() {
  //if (!myScreen.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {  //OLED 0.96
    if (!myScreen.begin(SCREEN_ADDRESS, true)) {                  //OLED 1.3
    //Serial.println(F("SSD1306 allocation failed"));
  }
  myScreen.clearDisplay();
  myScreen.drawBitmap(
    (myScreen.width() - LOGO_WIDTH) / 2,
    (myScreen.height() - LOGO_HEIGHT) / 2,
    icon, LOGO_WIDTH, LOGO_HEIGHT, 1);
  myScreen.display();
  step.setStorage(stepArr);
}

void gameOver(SnakeDir dir) {
  static bool overFirstFlag = true;
  if(overFirstFlag){
    gameOverFlag = true;
    overFirstFlag = false;
    myScreen.clearDisplay();
    myScreen.setTextSize(3);              
    myScreen.setTextColor(WHITE);  
    myScreen.setCursor(30, 10);         
    myScreen.println(F("GAME"));
    myScreen.setCursor(30, 40);  
    myScreen.println(F("OVER"));
    myScreen.display();
    longSnake = 22;
    head = {60, 24};
    tail = { head.X + longSnake, 24 };
    snakeDir = MOVE_LEFT;
    myScore = 0;
  }
  if(dir == MOVE_UP){
    delay(500);
    myScreen.clearDisplay();
    myScreen.display();
    SnakeDir d;
    for(int i = 0; i < 100; i ++){
      q.pop(&d);
    }
    step.clear();
    snakeDir = MOVE_LEFT;
    initSystem();
    gameOverFlag = false;
    overFirstFlag = true;
  }
}

void initSystem() {
  for (uint8_t i = 0; i < 129; i++) {
    myScreen.drawPixel(i, 51, WHITE);
    myScreen.drawPixel(i, 50, WHITE);
  } 
  for (int i = head.X; i < head.X + longSnake; i++) {
    myScreen.drawPixel(i, head.Y, WHITE);
    myScreen.drawPixel(i, head.Y + 1, WHITE);
  }
  for (int i = head.X; i < head.X + longSnake; i+=2) {
    step.push_back({i, head.Y});
  }
  for (int i = 0; i < longSnake / 2; i++) {
    q.push(&snakeDir);
  }
  randomBait(true);
  myScreen.setTextSize(1);         
  myScreen.setTextColor(WHITE); 
  myScreen.setCursor(0, 53);            
  myScreen.print("Score: ");
  myScreen.setCursor(40, 53);             
  myScreen.print("0");
  myScreen.display();
}

void baitDraw(uint8_t x, uint8_t y, uint8_t color) {
  myScreen.drawPixel(x, y, color);
  myScreen.drawPixel(x, y + 1, color);
  myScreen.drawPixel(x + 1, y, color);
  myScreen.drawPixel(x + 1, y + 1, color);
  myScreen.display();
}

void randomBait(bool flag) {
  if(gameOverFlag) return;
  if (flag) {
    //baitDraw(bait.X, bait.Y, BLACK);
    bait.X = random(0, 127);
    bait.Y = random(0, 49);
    if (bait.X % 2 != 0) bait.X += 1;
    if (bait.Y % 2 != 0) bait.Y += 1;
    intervalBait = millis();
    // Serial.println(bait.X);
    // Serial.println(bait.Y);
    // Serial.println("-----------");
  } else {
    baitDraw(bait.X, bait.Y, WHITE);
    if (millis() - intervalBait > 10000) {
      intervalBait = millis();
      baitDraw(bait.X, bait.Y, BLACK);
      bait.X = random(0, 127);
      bait.Y = random(0, 49);
      if (bait.X % 2 != 0) bait.X += 1;
      if (bait.Y % 2 != 0) bait.Y += 1;
    }
  }
}

void snakeErase(int a, int b, SnakeDir dir) {
  switch (dir) {
    case MOVE_UP:
    case MOVE_DOWN:
      myScreen.drawPixel(a, b, BLACK);
      myScreen.drawPixel(a + 1, b, BLACK);
      myScreen.drawPixel(a, b + 1, BLACK);
      myScreen.drawPixel(a + 1, b + 1, BLACK);
      break;
    case MOVE_LEFT:
    case MOVE_RIGHT:
      myScreen.drawPixel(a, b, BLACK);
      myScreen.drawPixel(a + 1, b, BLACK);
      myScreen.drawPixel(a, b + 1, BLACK);
      myScreen.drawPixel(a + 1, b + 1, BLACK);
      break;
  }
}

void snakeDraw(int a, int b, SnakeDir dir) {
  switch (dir) {
    case MOVE_UP:
    case MOVE_DOWN:
      myScreen.drawPixel(a, b, WHITE);
      myScreen.drawPixel(a + 1, b, WHITE);
      myScreen.drawPixel(a, b + 1, WHITE);
      myScreen.drawPixel(a + 1, b + 1, WHITE);
      break;
    case MOVE_LEFT:
    case MOVE_RIGHT:
      myScreen.drawPixel(a, b, WHITE);
      myScreen.drawPixel(a + 1, b, WHITE);
      myScreen.drawPixel(a, b + 1, WHITE);
      myScreen.drawPixel(a + 1, b + 1, WHITE);
      break;
  }
}

void push_front(Vector<SnakeStep>& vec, SnakeStep step) {
    vec.push_back({0,0});
    for (int i = vec.size() - 1; i > 0; i--) {
        vec[i] = vec[i - 1];
    }
    vec[0] = step; 
}

void headSnake(SnakeDir dir) {
  SnakeDir d = dir;
  switch (dir) {
    case MOVE_UP:
      head.Y -= 2;
      break;
    case MOVE_DOWN:
      head.Y += 2;
      break;
    case MOVE_LEFT:
      head.X -= 2;
      break;
    case MOVE_RIGHT:
      head.X += 2;
      break;
  }
  snakeDraw(head.X, head.Y, dir);
  q.push(&d);
  push_front(step, {head.X, head.Y});
}

void tailSnake(bool erase) {
  if (!erase) return;
  SnakeDir d;
  q.pop(&d);
  switch (d) {
    case MOVE_UP:
      tail.Y -= 2;
      break;
    case MOVE_DOWN:
      tail.Y += 2;
      break;
    case MOVE_LEFT:
      tail.X -= 2;
      break;
    case MOVE_RIGHT:
      tail.X += 2;
      break;
  }
  snakeErase(tail.X, tail.Y, d);
  step.pop_back();
}

bool eatBait() {
  switch (snakeDir) {
    case MOVE_UP:
    case MOVE_DOWN:
      if (head.Y == bait.Y && (head.X == bait.X || head.X == bait.X + 1 || head.X + 1 == bait.X || head.X + 1 == bait.X + 1)) return true;
      if (head.Y == bait.Y + 1 && (head.X == bait.X || head.X == bait.X + 1 || head.X + 1 == bait.X || head.X + 1 == bait.X + 1)) return true;
      break;
    case MOVE_LEFT:
    case MOVE_RIGHT:
      if (head.X == bait.X && (head.Y == bait.Y || head.Y == bait.Y + 1 || head.Y + 1 == bait.Y || head.Y + 1 == bait.Y + 1)) return true;
      if (head.X == bait.X + 1 && (head.Y == bait.Y || head.Y == bait.Y + 1 || head.Y + 1 == bait.Y || head.Y + 1 == bait.Y + 1)) return true;
      break;
  }
  return false;
}

bool snakeRun() {
  if(gameOverFlag) return false;
  if(head.X < 0 || head.X > 127 || head.Y < 0 || head.Y >= 50){
    return false;
  }
  for(uint8_t i = 1; i < step.size(); i++){
    if (head.Y == step[i].Y && (head.X == step[i].X || head.X == step[i].X + 1 || head.X + 1 == step[i].X || head.X + 1 == step[i].X + 1)) return false;
    if (head.Y == step[i].Y + 1 && (head.X == step[i].X || head.X == step[i].X + 1 || head.X + 1 == step[i].X || head.X + 1 == step[i].X + 1)) return false;
    if (head.X == step[i].X && (head.Y == step[i].Y || head.Y == step[i].Y + 1 || head.Y + 1 == step[i].Y || head.Y + 1 == step[i].Y + 1)) return false;
    if (head.X == step[i].X + 1 && (head.Y == step[i].Y || head.Y == step[i].Y + 1 || head.Y + 1 == step[i].Y || head.Y + 1 == step[i].Y + 1)) return false;
  }
  if (millis() - intervalSnake > 100) { // toc do chay
    intervalSnake = millis();
    bool e = true;
    headSnake(snakeDir);
    if (eatBait()) {
      myScore++;
      randomBait(true);
      e = false;
    }
    tailSnake(e);
    myScreen.display();
  }
  return true;
}

void score(){
  if(gameOverFlag) return;
  static uint16_t lastScore = myScore;
  if(lastScore != myScore){            
    myScreen.setTextColor(BLACK);  
    myScreen.setCursor(40, 53);           
    myScreen.print(String(lastScore));
    myScreen.setTextColor(WHITE);
    myScreen.setCursor(40, 53);             
    myScreen.print(String(myScore));
    myScreen.display();
    lastScore = myScore;
  }
}
