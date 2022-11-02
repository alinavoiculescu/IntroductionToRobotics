#define NOTE_C3 131

const unsigned int bitsPerSecond = 9600;
const unsigned int buzzerPin = 4;
const unsigned int greenLedPinPedestrians = 5;
const unsigned int redLedPinPedestrians = 6;
const unsigned int buttonPin = 7;
const unsigned int greenLedPinCars = 8;
const unsigned int yellowLedPinCars = 9;
const unsigned int redLedPinCars = 10;
const unsigned int delayAfterButtonPress = 8000;
const unsigned int durationState2 = 3000;
const unsigned int durationState3 = 8000;
const unsigned int durationState4 = 4000;
const unsigned int buzzerInterval = 1000;
const unsigned int buzzerIntervalEnding = 500;

unsigned int currentState = 1;
volatile byte buttonState = 0;
unsigned long buzzerMillis = 0;
unsigned long millisBeforeState;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(greenLedPinPedestrians, OUTPUT);
  pinMode(redLedPinPedestrians, OUTPUT);

  pinMode(greenLedPinCars, OUTPUT);
  pinMode(yellowLedPinCars, OUTPUT);
  pinMode(redLedPinCars, OUTPUT);
  
  Serial.begin(bitsPerSecond);
}

void loop() {
  if (currentState == 1) {
    buttonState = digitalRead(buttonPin);

    if (!buttonState) {
      moveToNextState();
    }
    else {
      greenSemaphoreCars();
    }
  }
  else if (currentState == 2) {
    greenSemaphoreCarsEnding(millisBeforeState);
  }
  else if (currentState == 3) {
    greenSemaphorePedestrians(millisBeforeState);
  }
  else if (currentState == 4) {
    greenSemaphorePedestriansEnding(millisBeforeState);
  }
}

// State 2
void greenSemaphoreCarsEnding(unsigned long millisBeforeState) {
  unsigned long currentMillis = millis();
  unsigned long millisAfterDelay = delayAfterButtonPress + durationState2;

  if (currentMillis - millisBeforeState >= delayAfterButtonPress) {
    yellowSemaphoreCars();
  }
  
  if (currentMillis - millisBeforeState >= millisAfterDelay) {
    moveToNextState();
  }
}

// State 3
void greenSemaphorePedestrians(unsigned long millisBeforeState) {
  unsigned long currentMillis = millis();

  if (currentMillis - millisBeforeState <= durationState3) {
    greenSemaphorePedestrians();
    buzzerSound(buzzerInterval);
  }
  else {
    moveToNextState();
  }
}

// State 4
void greenSemaphorePedestriansEnding(unsigned long millisBeforeState) {
  unsigned long currentMillis = millis();
  
  if (currentMillis - millisBeforeState <= durationState4) {
    buzzerSoundAndBlinking(buzzerIntervalEnding);
  }
  else {
    moveToNextState();
  }
}

void greenSemaphoreCars() {
  digitalWrite(redLedPinPedestrians, HIGH);
  digitalWrite(greenLedPinPedestrians, LOW);
  digitalWrite(greenLedPinCars, HIGH);
  digitalWrite(yellowLedPinCars, LOW);
  digitalWrite(redLedPinCars, LOW);
}

void greenSemaphorePedestrians() {
  digitalWrite(redLedPinPedestrians, LOW);
  digitalWrite(greenLedPinPedestrians, HIGH);
  digitalWrite(greenLedPinCars, LOW);
  digitalWrite(yellowLedPinCars, LOW);
  digitalWrite(redLedPinCars, HIGH);
}

void yellowSemaphoreCars() {
  digitalWrite(redLedPinPedestrians, HIGH);
  digitalWrite(greenLedPinPedestrians, LOW);
  digitalWrite(greenLedPinCars, LOW);
  digitalWrite(yellowLedPinCars, HIGH);
  digitalWrite(redLedPinCars, LOW);
}

void moveToNextState() {
  if (currentState == 4) {
    currentState = 1;
  }
  else {
    currentState++;
  }

  millisBeforeState = millis();
}

void buzzerSound(unsigned long buzzerInterval) {
  buzzerSoundAndBlinking(buzzerInterval, false);
}

void buzzerSoundAndBlinking(unsigned long buzzerInterval) {
  buzzerSoundAndBlinking(buzzerInterval, true);
}

void buzzerSoundAndBlinking(unsigned long buzzerInterval, byte blinking) {
  unsigned long currentMillis = millis();

  if (currentMillis - buzzerMillis >= buzzerInterval) {
    buzzerMillis = currentMillis;
  
    const unsigned int buzzerDuration = buzzerInterval / 2;

    tone(buzzerPin, NOTE_C3, buzzerDuration);
      
    if (blinking) {
      digitalWrite(greenLedPinPedestrians, !digitalRead(greenLedPinPedestrians));
    }
  }
}