#include <LedControl.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte matrixSize = 8;
const byte rsPin = 9;
const byte enablePin = 8;
const byte d4Pin = 7;
const byte d5Pin = 6;
const byte d6Pin = 5;
const byte d7Pin = 4;
const byte noOfLcdCols = 16;
const byte noOfLcdRows = 2;
const byte joyPinX = A0;
const byte joyPinY = A1;
const byte joyPinSW = 2;
const byte noOfMenuItems = 5;
const char* menuItems[] = {
  "   Start Game   ",
  "   Highscore    ",
  "    Settings    ",
  "     About      ",
  "  How to Play   "
  };
const byte noHighscores = 3;
const int blinkingInterval = 500;
const int lowerThreshold = 400;
const int upperThreshold = 600;

LedControl matrix = LedControl(dinPin, clockPin, loadPin, 1);
LiquidCrystal lcd = LiquidCrystal(rsPin, enablePin, d4Pin, d5Pin, d6Pin, d7Pin);

int playerX = 0;
int playerY = 0;
int foodX = 0;
int foodY = 0;
int score = 0;
int lives = 3;
byte joyXIsNeutral = true;
byte joyYIsNeutral = true;
byte menuIdx = 0;
byte buttonPressed = false;

struct Highscore {
  String name;
  String score;
};
Highscore highscores[noHighscores];

byte blinkingState = true;
unsigned int lastBlinkingTime = 0;

void setup() {
  pinMode(joyPinSW, INPUT_PULLUP);
  initializeMatrix();
  initializeLcd();
  printGreetingMessage();
  wait(3000);
  readHighscores();
}

void loop() {
  menuLoop();
}

void initializeMatrix() {
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);
}

void initializeLcd() {
  lcd.begin(16, 2);
  lcd.clear();  
}

void printGreetingMessage() {
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Snake!");
  lcd.setCursor(0, 1);
  lcd.print("(almost snake..)");
}

void readHighscores() {
  int positionCount = 0;
  for (int i = 0; i < noHighscores; i++) {
    highscores[i].name = (char)EEPROM.read(positionCount);
    highscores[i].name += (char)EEPROM.read(positionCount + 1);
    highscores[i].name += (char)EEPROM.read(positionCount + 2);
    highscores[i].name += (char)EEPROM.read(positionCount + 3);
    highscores[i].score = (char)EEPROM.read(positionCount + 4);
    positionCount += 5;
    if (highscores[i].score.length() == 1) {
      highscores[i].score = "00" + highscores[i].score;
    }
    else if (highscores[i].score.length() == 2) {
      highscores[i].score = "0" + highscores[i].score;
    }
  }
}

void wait(unsigned int milliseconds) {
  unsigned long startTime = millis();
  while (millis() - startTime < milliseconds) { }
}

void printMenuItem() {
  lcd.setCursor(0, 0);
  lcd.print(menuItems[menuIdx]);
  lcd.setCursor(0, 1);
  lcd.print("<-------------->");
}

void scrollMenuItems() {
  int joyValueX = analogRead(joyPinX);
  int joyValueY = analogRead(joyPinY);
  if (joyValueY < lowerThreshold && joyYIsNeutral && menuIdx > 0) {
    joyYIsNeutral = false;
    menuIdx--;
  } else if (joyValueY > upperThreshold && joyYIsNeutral && menuIdx < noOfMenuItems - 1) {
    joyYIsNeutral = false;
    menuIdx++;
  }
  else if (joyValueY >= lowerThreshold && joyValueY <= upperThreshold) {
    joyYIsNeutral = true;
  }
}

void showHighscores() {
  byte firstHighscores = true;
  lcd.clear();
  unsigned int startTime = millis();
  do {
    printHighscores(firstHighscores);
    scrollHighscores(firstHighscores); 
  }  while (millis() - startTime <= 6000);
}

void printHighscores(byte &firstHighscores) {
  byte fromNumber;
  byte toNumber;
  byte count = 0;
  byte line;
  if (firstHighscores) {
    fromNumber = 0;
    toNumber = 2; 
  }
  else {
    fromNumber = 1;
    toNumber = 3;
  }
  for (int i = fromNumber; i < toNumber; i++) {
    String stringToDisplay = getHighscore(i);
    if (!count) {
      line = 0;
    }
    else {
      line = 1;
    }
    scrollTextOnDisplayLine(stringToDisplay, line);
    if (!line) {
      lcd.print("^");
    }
    else {
      lcd.print("v");
    }
    count++;
  }
}

void scrollHighscores(byte &firstHighscores) {
  int joyValueX = analogRead(joyPinX);
  if (joyValueX < lowerThreshold && joyXIsNeutral) {
    joyXIsNeutral = false;
    firstHighscores = false;
  } else if (joyValueX > upperThreshold && joyXIsNeutral) {
    joyXIsNeutral = false;
    firstHighscores = true;
  }
  else {
    joyXIsNeutral = true;
  }  
}

String getHighscore(int position) {
  return (String)(position + 1) + ". " + highscores[position].name + " " + highscores[position].score + "    ";
}

void printCurrentDifficulty(byte difficulty) {
  lcd.setCursor(0, 0);
  lcd.print("   Current: ");
  lcd.print(difficulty);
  lcd.print("   ");
  lcd.setCursor(0, 1);
  switch (difficulty) {
    case 1:
      lcd.print("      EASY      ");
      break;
    case 2:
      lcd.print("     MEDIUM     ");
      break;
    case 3:
      lcd.print("      HARD      ");
      break;
  }
}

byte scrollDifficulty(byte difficulty) {
  int joyValueX = analogRead(joyPinX);
  if (joyValueX < lowerThreshold && difficulty > 1 && joyXIsNeutral) {
    joyXIsNeutral = false;
    difficulty--;
  } else if (joyValueX > upperThreshold && difficulty < 3  && joyXIsNeutral) {
    joyXIsNeutral = false;
    difficulty++;
  } else if (joyValueX >= lowerThreshold && joyValueX <= upperThreshold) {
    joyXIsNeutral = true;
  }
  return difficulty;
}

void updateDifficulty(byte difficulty) {
  unsigned long startTime = millis();
  do {
    difficulty = scrollDifficulty(difficulty);
    printCurrentDifficulty(difficulty);
  } while (millis() - startTime <= 4000);
  EEPROM.update(16, difficulty);
}

void showSettings() {
  lcd.clear();
  byte difficulty = EEPROM.read(16);
  printCurrentDifficulty(difficulty);
  updateDifficulty(difficulty);
  wait(3000);
}

void showAboutInfo() {
  lcd.clear();
  showGameAndCreator();
  showGitHub();
}

void showGameAndCreator() {
  lcd.setCursor(0, 0);
  scrollTextOnDisplayLine("Snake v1.0 created by Alina Voiculescu", 0);
}

void showGitHub() {
  lcd.setCursor(0, 1);
  scrollTextOnDisplayLine("GitHub user: alinavoiculescu", 1);
  wait(600);
  scrollTextOnDisplayLine("GitHub repo: IntroductionToRobotics", 1);
  wait(3000);
}

void showInstructions() {
  lcd.clear();
  lcd.setCursor(0, 0);
  scrollTextOnDisplayLine("Use the joystick to collect food", 0);
  lcd.setCursor(0, 1);
  scrollTextOnDisplayLine("Get the best highscore ever!", 1);
  wait(3000);
}

void updateMenu() {
  int joySWCurrentState = digitalRead(joyPinSW);
  if (joySWCurrentState == LOW && !buttonPressed) {
    buttonPressed = true;
    if (menuIdx == 0) {
      gameLoop();
    } else if (menuIdx == 1) {
      showHighscores();
    } else if (menuIdx == 2) {
      showSettings();
    } else if (menuIdx == 3) {
      showAboutInfo();
    } else if (menuIdx == 4) {
      showInstructions();
    }
    resetMenu();
  }
  buttonPressed = false;
}

void resetMenu() {
  menuIdx = 0;
  clearMatrix();
  lcd.clear();
  printMenuItem();
}

void menuLoop() {
  printMenuItem();
  scrollMenuItems();
  updateMenu();
}

void clearMatrix() {
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      matrix.setLed(0, i, j, false);
    }
  }
}

void generateFood() {
  foodX = random(0, matrixSize);
  foodY = random(0, matrixSize);
  while (foodX == playerX && foodY == playerY) {
    foodX = random(0, matrixSize);
    foodY = random(0, matrixSize);
  }
}

void generatePlayerInitialPosition() {
  playerX = random(0, matrixSize);
  playerY = random(0, matrixSize);
  while (playerX == foodX  && playerY == foodY) {
    playerX = random(0, matrixSize);
    playerY = random(0, matrixSize);
  }
}

int setSpeed() {
  byte difficulty = EEPROM.read(16);
  int speed = 0;
  switch (difficulty) {
    case 1:
      speed = 500;
      break;
    case 2:
      speed = 300;
      break;
    case 3:
      speed = 100;
      break;
  }
  return speed;
}

void showGameLcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lives:");
  lcd.print(lives + " ");
  lcd.setCursor(7, 0);
  lcd.print(" Score:");
  lcd.print(score + " ");
  lcd.setCursor(0, 1);
  lcd.print(" EAT THAT FOOD! ");
}

void updatePlayerPosition() {
  int joyValueX = analogRead(joyPinX);
  int joyValueY = analogRead(joyPinY);
  if (joyValueX < lowerThreshold && playerX > 0) {
    playerX--;
  } else if (joyValueX > upperThreshold && playerX < matrixSize - 1) {
    playerX++;
  }
  if (joyValueY < lowerThreshold && playerY > 0) {
    playerY--;
  } else if (joyValueY > upperThreshold && playerY < matrixSize - 1) {
    playerY++;
  }
}

void updateGameLcd() {
  lcd.setCursor(6, 0);
  lcd.print(lives);
  lcd.setCursor(14, 0);
  if (((String)score).length() == 1) {
    lcd.print(0);
    lcd.print(score);
  }
  else {
    lcd.print(score);
  }
}

void checkIfFoodCollected() {
  if (playerX == foodX && playerY == foodY) {
      generateFood();
      score++;
  }
}

void showMatrixCongrats() {
  for (int i = 0; i < 8; i++) {
    matrix.setChar(i, 0, 'C', false);
    matrix.setChar(i, 1, 'O', false);
    matrix.setChar(i, 2, 'N', false);
    matrix.setChar(i, 3, 'G', false);
    matrix.setChar(i, 4, 'R', false);
    matrix.setChar(i, 5, 'A', false);
    matrix.setChar(i, 6, 'T', false);
    matrix.setChar(i, 7, 'S', false);
  }
  wait(2000);
}

void checkIfHighscore() {
  if ((String)score > highscores[0].score) {
    // TODO: "PLEASE WRITE YOUR NAME (4 LETTERS)"
    highscores[2] = highscores[1];
    highscores[1] = highscores[0];
    // highscores[0].name = NEW NAME;
    highscores[0].score = score;
    // EEPROM update
    showMatrixCongrats();
  }
  else if ((String)score > highscores[1].score) {
    // TODO: "PLEASE WRITE YOUR NAME (4 LETTERS)"
    highscores[1] = highscores[0];
    // highscores[1].name = NEW NAME;
    highscores[1].score = score;
    // EEPROM update
    showMatrixCongrats();
  }
  else if ((String)score > highscores[0].score) {
    // TODO: "PLEASE WRITE YOUR NAME (4 LETTERS)"
    // highscores[1].name = NEW NAME;
    highscores[1].score = score;
    // EEPROM update
    showMatrixCongrats();
  }
}

void gameLoop() {
  int speed = setSpeed();
  score = 0;
  lives = 3;
  generatePlayerInitialPosition();
  matrix.setLed(0, playerX, playerY, true);
  generateFood();
  blinkFood();
  showGameLcd();
  while (lives > 0) {
    updatePlayerPosition();
    clearMatrix();
    matrix.setLed(0, playerX, playerY, true);
    blinkFood();
    updateGameLcd();
    checkIfFoodCollected();
    wait(speed);
  }
  checkIfHighscore();
  resetMenu();
}

void scrollTextOnDisplayLine(String text, byte line) {
  int positionCount = 0;
  int textLength = text.length();
  char textArray[40];
  lcd.setCursor(0, line);
  if (textLength <= 16) {
    lcd.print(text);
  }
  else if (textLength > 39) {
    lcd.print(text.substring(0, 40));
    while (textLength != 0) {
      wait(600);
      lcd.scrollDisplayLeft();
      textLength--;
    }
    lcd.setCursor(0, line);
    lcd.print(text.substring(40));
    textLength = text.length() - 41;
    while (text.length() > 0) {
      lcd.scrollDisplayLeft();
      wait(600);
      textLength--;
    }
  }
  else if (textLength <= 39) {
    lcd.print(text);
    while (textLength > 16) {
      wait(600);
      lcd.scrollDisplayLeft();
      textLength--;
    }
    while (textLength != text.length()) {
      wait(200);
      lcd.scrollDisplayRight();
      textLength++;
    }  
  }
}

void blinkFood() {
  if (millis() - lastBlinkingTime >= blinkingInterval) {
    blinkingState = !blinkingState;
    lastBlinkingTime = millis();
  }
  matrix.setLed(0, foodX, foodY, blinkingState);
}
