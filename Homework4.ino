#include <EEPROM.h>

// shift register pins
const int dataPin = 12; // DS
const int latchPin = 11; // STCP
const int clockPin = 10; // SHCP

// joystick pins
const int pinSW = 3;
const int pinX = A0;
const int pinY = A1;

const int minThreshold = 350;
const int maxThreshold = 700;

// digital point delay
const int dpDelay = 500;
const int minDigit = 0;
const int maxDigit = 15;

// interrupt debounce
const int interruptDelay = 200;

// values for joystick
volatile boolean state = false; // false = state 1; true = state 2

int xValue = 0;
int yValue = 0;
bool joyXMoved = false;
bool joyYMoved = false;

// values for display
int digits[4] = {0, 0, 0, 0};
bool points[4] = {0, 0, 0, 0};
int currentDisplay = 0;

// timer for digital point
long lastDpTime = 0;

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int displayCount = 3;

const int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

int digitArray[16] = {
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
  B00111110, // B
  B10011100, // C
  B01111010, // D
  B10011110, // E
  B10001110  // F
};

bool reading = 0;
bool lastButtonState = 0;
bool lastReading = 0;
bool buttonPressed = 0;
bool buttonState = 0;
bool buttonPressedState = 0;

const int debounceDelayPressed = 50;
const int longDebounceTimePressLong = 3000;

unsigned long longPressedTime = 0;
unsigned long lasDebounceTimePressed = 0 ;
unsigned long lastDebounceTimePressed = 0; 

void setup() {
  // shift register
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // joystick button 
  pinMode(pinSW, INPUT_PULLUP);
 
  // joystick axes
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  for (int i = 0; i <= displayCount; ++i) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
   }

  readEEPROM();
  Serial.begin(9600);
}
void loop() {
  buttonCheck();
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  if (!buttonPressed) {
    state1();
  } 
  else { 
    state2();  
  }
  Serial.println(state);
  writeDigits();
}
// read last value from EEPROM
void readEEPROM () {
  for (int i = 0; i <= displayCount; ++i) {
    digits[i] = EEPROM.read(i);
  }
}

// select only one display
void showDigit(int digit) {
  for (int i = 0; i <= displayCount; ++i) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[digit], LOW);
}

// write digit and digital point to shift register
void writeReg(int digit, int dpState) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit + dpState);
  digitalWrite(latchPin, HIGH);
}

// write digits on display
void writeDigits() {
  for (int i = 0; i <= displayCount; ++i) {
    showDigit(i);
    writeReg(digitArray[digits[i]], points[i]);
    EEPROM.write(i, digits[i]);
  
    delay(3);
  }
}
void resetDigits() {
  for(int i=0; i<=displayCount; ++i){
      digits[i]=0;
      points[i]=0; 
  }
  points[currentDisplay] = 1;

}

void blinkPoint(){ 
  if (millis() - lastDpTime > dpDelay) { // blinking digital point
      points[currentDisplay] = !points[currentDisplay];
      lastDpTime = millis();
  }
}

void state1(){
  if (xValue < minThreshold && !joyXMoved) { 
      if (currentDisplay < displayCount) { 
        points[currentDisplay] = false; 
        ++currentDisplay; 
      }
      joyXMoved = true; 
    } 
  if (xValue > maxThreshold && !joyXMoved) { 
      if (currentDisplay > 0) {
        points[currentDisplay] = false;
        --currentDisplay;
      }
      joyXMoved = true;
  }
  if (xValue > minThreshold && xValue < maxThreshold) {
      joyXMoved = false;
    }
    blinkPoint();
  
}


void state2(){
  points[currentDisplay] = true; 
    if (yValue < minThreshold && !joyYMoved) {
      if (digits[currentDisplay] < maxDigit) {
        ++digits[currentDisplay];
      }
      joyYMoved = true; 
    } 
    if (yValue > maxThreshold && !joyYMoved) {
      if (digits[currentDisplay] > minDigit) {
        --digits[currentDisplay];
      }
      joyYMoved = true;
    }
    if (yValue > minThreshold && yValue < maxThreshold) {
      joyYMoved = false;
    }
}

void buttonCheck() { 
  reading = digitalRead(pinSW);
  if (reading != lastButtonState) {
    lastDebounceTimePressed = millis();
  }

  if(buttonState == 0){
    if(reading!=lastReading){
      longPressedTime = millis();  
    }
    lastReading = reading;
    if(millis()-longPressedTime > longDebounceTimePressLong ){
      buttonPressed = 0;
      longPressedTime = millis();
      currentDisplay = 0;
      resetDigits();
    }
  }
 
  if (millis() - lastDebounceTimePressed > debounceDelayPressed) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW ) {
        if (!buttonPressed) {
          buttonPressed = 1;
          
        }
        else{
          buttonPressed = 0;    
        }
      }  
    }
  }
  lastButtonState = reading;      
  }