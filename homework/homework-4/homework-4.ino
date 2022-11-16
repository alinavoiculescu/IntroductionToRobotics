const int bitsPerSecond = 9600;

const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12;
 
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int joyPinX = A0;
const int joyPinY = A1;
const int joyPinSW = 2;
 
const byte regSize = 8;

const int displayCount = 4;

const int encodingsNumber = 16;

const int lowerThreshold = 400;
const int upperThreshold = 600;
const int valueBetweenThresholds = 500;

const int rightMostDisplay = 0;
const int leftMostDisplay = displayCount - 1;

const int firstDigit = 0;
const int lastDigit = encodingsNumber - 1;

const int blinkingInterval = 500;
const int longPressInterval = 2000;
const int shortPressInterval = 50;
const int debounceInterval = 100;

int displayDigits[displayCount] = {
  segD1, segD2, segD3, segD4
};

byte joyXIsNeutral = true;
byte joyYIsNeutral = true;

byte joySWState = HIGH;
byte joyCurrentSWState = LOW;
byte joyPrevSWState = HIGH;

byte currentDisplay = 0;
byte currentState = 1;

int digitsDisplayed[displayCount];

int byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

unsigned long prevBlinking;

int pressedTime = 0;
int releasedTime = 0;
int pressesNo = 0;

int joyX;
int joyY;

unsigned long previousDebounceTime;
unsigned long previousMillisWriteNumber;
 
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(joyPinSW, INPUT_PULLUP);
 
  for (int displayNo = 0; displayNo < displayCount; ++displayNo) {
    pinMode(displayDigits[displayNo], OUTPUT);
    digitalWrite(displayDigits[displayNo], LOW);
  }

  Serial.begin(bitsPerSecond);
}
 
void loop() {
  joyX = analogRead(joyPinX);
  joyY = analogRead(joyPinY);

  if (currentState == 1) {
    makeNextMovement(valueBetweenThresholds, joyY);
  }
  else if (currentState == 2) {
    makeNextMovement(joyX, valueBetweenThresholds);
  }

  handleButtonPressing();

  writeNumberOnDisplay(currentDisplay);
}

void handleButtonPressing() {
  joyCurrentSWState = digitalRead(joyPinSW);
 
  if (joyCurrentSWState != joyPrevSWState) {
    previousDebounceTime = millis();
  }

  if (millis() - previousDebounceTime > debounceInterval) {
    if (joyCurrentSWState != joySWState) {
      joySWState = joyCurrentSWState;

      if (joySWState == LOW) {
        pressedTime = millis();
      }
      else {
        releasedTime = millis();
      }
      
      if (releasedTime - pressedTime > longPressInterval && currentState == 1) {
        backToBeginning();
      }
      else if (releasedTime - pressedTime > shortPressInterval) {
        pressesNo++;

        if (pressesNo % 2) {
          currentState = 2;
        }
        else {
          currentState = 1;
        }
      }
    }
  }
 
  joyPrevSWState = joyCurrentSWState;
}

void makeNextMovement(int joyX, int joyY) {
  Serial.println(currentDisplay);
  if (joyX < lowerThreshold && joyXIsNeutral) {
    joyXIsNeutral = false;

    if (digitsDisplayed[currentDisplay] < lastDigit) {
      digitsDisplayed[currentDisplay]++;
    }
  }
  else if (joyX > upperThreshold && joyXIsNeutral) {
    joyXIsNeutral = false;

    if (digitsDisplayed[currentDisplay] > firstDigit) {
      digitsDisplayed[currentDisplay]--;
    }
  }
  else if (joyX >= lowerThreshold && joyX <= upperThreshold) {
    joyXIsNeutral = true;
  }

  if (joyY < lowerThreshold && joyYIsNeutral) {
    joyYIsNeutral = false;

    if (currentDisplay > rightMostDisplay) {
      currentDisplay--;
    }
  }
  else if (joyY > upperThreshold && joyYIsNeutral) {
    joyYIsNeutral = false;

    if (currentDisplay < leftMostDisplay ) {
      currentDisplay++;
    }
  }
  else if (joyY >= lowerThreshold && joyY <= upperThreshold) {
    joyYIsNeutral = true;
  }
}
 
void writeReg(int digit) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    digitalWrite(latchPin, HIGH);
}
 
void activateDisplay(int displayNumber) {
  for (int displayNo = 0; displayNo < displayCount; ++displayNo) {
    digitalWrite(displayDigits[displayNo], HIGH);
  }

  digitalWrite(displayDigits[displayNumber], LOW);
}
 
void writeNumberOnDisplay(byte display) {
  for (int displayNo = 0; displayNo < displayCount; ++displayNo) {
    int digitToDisplay = 0;

    if (displayNo == display && currentState == 1) {
      digitToDisplay = addDpBlinking(displayNo);
    }
    else if (displayNo == display && currentState == 2) {
      digitToDisplay = byteEncodings[digitsDisplayed[displayNo]] ^ 1; 
    }
    else {
      digitToDisplay = byteEncodings[digitsDisplayed[displayNo]];
    }

    writeReg(digitToDisplay);
    activateDisplay(displayNo);

    while (millis() - previousMillisWriteNumber <= 5);
    previousMillisWriteNumber = millis(); 
  }
}

int addDpBlinking(byte display) {
  int digit = byteEncodings[digitsDisplayed[display]];
  int dpOn = blinkingInterval;
  int dpOff = blinkingInterval * 2;

  if (millis() - prevBlinking >= dpOn) {
    digit = byteEncodings[digitsDisplayed[display]] ^ 1;

    if (millis() - prevBlinking >= dpOff) {
      prevBlinking = millis();
    }
  }

  return digit;
}

void backToBeginning() {
  for (int displayNo = 0; displayNo < displayCount; ++displayNo) {
    digitsDisplayed[displayNo] = firstDigit;
  }

  currentDisplay = rightMostDisplay;
}