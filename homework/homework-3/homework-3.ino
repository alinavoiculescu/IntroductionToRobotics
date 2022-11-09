const int bitsPerSecond = 9600;

const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

const int joyPinX = A0;
const int joyPinY = A1;
const int joyPinSW = 2;

const byte segmentsNo = 8;

const byte segments[segmentsNo] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

const byte positionsNo = 4;

const byte notApplicable = -1;
const byte segmentA = 0;
const byte segmentB = 1;
const byte segmentC = 2;
const byte segmentD = 3;
const byte segmentE = 4;
const byte segmentF = 5;
const byte segmentG = 6;
const byte segmentDP = 7;

const byte positionUp = 0;
const byte positionDown = 1;
const byte positionLeft = 2;
const byte positionRight = 3;
 
const int lowerThreshold = 400;
const int upperThreshold = 600;
const int valueBetweenThresholds = 500;

const int blinkingInterval = 500;
const int longPressInterval = 2000;
const int shortPressInterval = 50;
const int debounceDelay = 100;

unsigned long lastDebounceTime;

const byte movements[segmentsNo][positionsNo] = {
  //   UP            DOWN          LEFT           RIGHT
  { notApplicable, segmentG,      segmentF,      segmentB },      // SEGMENT A
  { segmentA,      segmentG,      segmentF,      notApplicable }, // SEGMENT B
  { segmentG,      segmentD,      segmentE,      segmentDP },     // SEGMENT C
  { segmentG,      notApplicable, segmentE,      segmentC },      // SEGMENT D
  { segmentG,      segmentD,      notApplicable, segmentC },      // SEGMENT E
  { segmentA,      segmentG,      notApplicable, segmentB },      // SEGMENT F
  { segmentA,      segmentD,      notApplicable, notApplicable }, // SEGMENT G
  { notApplicable, notApplicable, segmentC,      notApplicable }  // SEGMENT DP
};

byte pinStates[segmentsNo] = {
// pinA  pinB  pinC  pinD  pinE  pinF  pinG  pinDP
   LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW
};

byte currentSegment = segmentDP;
byte currentState = 1;

byte segmentNotBlinking = 0;
byte currentBlinkingState = 0;
 
byte joyXIsNeutral = true;
byte joyYIsNeutral = true;
byte joySWState = HIGH;
byte joyCurrentSWState = LOW;
byte joyPrevSWState = HIGH;

int pressedTime = 0;
int releasedTime = 0;
int pressesNo = 0;

int joyX;
int joyY;

unsigned long previousMillis;
 
void setup() {
  for (int i = 0; i < segmentsNo; i++) {
    pinMode(segments[i], OUTPUT);
  }
 
  pinMode(joyPinSW, INPUT_PULLUP);

  Serial.begin(bitsPerSecond);
}
 
void loop() {
  initalizeSegments();

  joyX = analogRead(joyPinX);
  joyY = analogRead(joyPinY);
  
  if (currentState == 1) {
    state1();
  }
  else if (currentState == 2) {
    state2();
  }

  handleButtonPressing();
}

void state1() {
  byte newPosition = getPositionToMove(joyX, joyY);

  if (newPosition == positionUp || newPosition == positionDown) {
    if (movements[currentSegment][newPosition] != notApplicable && joyXIsNeutral) {
      currentSegment = movements[currentSegment][newPosition];
      joyXIsNeutral = false;
    }
  }
  else if (newPosition == positionLeft || newPosition == positionRight) {
    if (movements[currentSegment][newPosition] != notApplicable && joyYIsNeutral) {
      currentSegment = movements[currentSegment][newPosition];
      joyYIsNeutral = false;
    }
  }
  else if (newPosition == notApplicable) {
    joyXIsNeutral = true;
    joyYIsNeutral = true;
  }
}

void state2() {
  byte newPosition = getPositionToMove(joyX, valueBetweenThresholds);

  if (joyXIsNeutral) {
    if (newPosition == positionUp) {
      currentBlinkingState = 1;
    }
    else if (newPosition == positionDown) {
      currentBlinkingState = 0;
    }

    joyXIsNeutral = false;
  }
  else {
    joyXIsNeutral = true;
  }
}

void initalizeSegments() {
  for (int i = 0; i < segmentsNo; i++) {
    digitalWrite(segments[i], pinStates[i]);
  }

  segmentBlink();

  digitalWrite(segments[currentSegment], currentBlinkingState);
}

void segmentBlink() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > blinkingInterval && segmentNotBlinking == 0) {
    previousMillis = currentMillis;

    currentBlinkingState = !currentBlinkingState;
  }
}

void moveCurrentSegment(byte ToSegment) {
  pinStates[currentSegment] = LOW;
  pinStates[ToSegment] = HIGH;

  currentSegment = ToSegment;
}

byte getPositionToMove(int joyX, int joyY) {
  if (joyX < lowerThreshold) {
    return positionDown;
  }
  else if (joyX > upperThreshold) {
    return positionUp;
  }
    
  if (joyY < lowerThreshold) {
    return positionLeft;
  }
  else if (joyY > upperThreshold) {
    return positionRight;
  }

  return notApplicable;
}

void backToBeginning() {
  for (int i = 0; i < segmentsNo; i++) {
    pinStates[i] = LOW;
  }

  currentSegment = segmentDP;

  currentState = 1;
}

void handleButtonPressing() {
  joyCurrentSWState = digitalRead(joyPinSW);
 
  if (joyCurrentSWState != joyPrevSWState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
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
          segmentNotBlinking = 1;
          currentState = 2;
        }
        else {
          pinStates[currentSegment] = currentBlinkingState;
          segmentNotBlinking = 0;
          currentState = 1;
        }
      }
    }
  }
 
  joyPrevSWState = joyCurrentSWState;
}
