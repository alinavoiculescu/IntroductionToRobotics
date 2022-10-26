const int bitsPerSecond = 9600;

const int redAnalogPin = A0;
const int greenAnalogPin = A1;
const int blueAnalogPin = A2;

const int redLedPin = 11;
const int greenLedPin = 10;
const int blueLedPin = 9;

const int minAnalogValue = 0;
const int maxAnalogValue = 1023;

const int minBrightnessValue = 0;
const int maxBrightnessValue = 255;

int redAnalogValue;
int greenAnalogValue;
int blueAnalogValue;

int redLedValue;
int greenLedValue;
int blueLedValue;

void setup() {
  pinMode(redAnalogPin, INPUT);
  pinMode(greenAnalogPin, INPUT);
  pinMode(blueAnalogPin, INPUT);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  Serial.begin(bitsPerSecond);
}

void loop() {
  redAnalogValue = analogRead(redAnalogPin);
  greenAnalogValue = analogRead(greenAnalogPin);
  blueAnalogValue = analogRead(blueAnalogPin);

  redLedValue = getBrightnessValue(redAnalogValue);
  greenLedValue = getBrightnessValue(greenAnalogValue);
  blueLedValue = getBrightnessValue(blueAnalogValue);

  setColor(redLedValue, greenLedValue, blueLedValue);
}

// get brightness value by mapping analog value to brightness value
int getBrightnessValue(int analogValue) {
  return map(analogValue, minAnalogValue, maxAnalogValue, minBrightnessValue, maxBrightnessValue);
}

void setColor(int redBrightness, int greenBrightness, int blueBrightness) {
  analogWrite(redLedPin, redBrightness);
  analogWrite(greenLedPin, greenBrightness);
  analogWrite(blueLedPin, blueBrightness);
}
