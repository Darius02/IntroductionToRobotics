#define STATE_CARS_CROSSING 0
#define STATE_YELLOW_LIGHT 1
#define STATE_PEDESTRIANS_CROSSING 2
#define STATE_PEDESTRIANS_BLINKING 3

#define STATE_CARS_CROSSING_DURATION 10000
#define STATE_YELLOW_LIGHT_DURATION 3000
#define STATE_PEDESTRIANS_CROSSING_DURATION 10000
#define STATE_PEDESTRIANS_BLINKING_DURATION 5000

#define STATE_IDLE -1  // resetting the system

#define STATE_BUTTON_PRESSED 1
#define STATE_BUTTON_RELEASED 0

const int buzzerPin = 3,
  buttonPin = 4,

  carLedRed = 9,
  carLedYellow = 8,
  carLedGreen = 7,

  pedestrianLedRed = 6,
  pedestrianLedGreen = 5;

int buttonState = LOW,
  lastButtonState = LOW,
  currentTime = 0,
  lastChangeTime = STATE_IDLE; // last time a state changed

unsigned int lastDebounceTime = 0,
  debounceDelay = 50,

  pedestrianGreenLedState = LOW,
  pedestrianLedBlinkingInterval = 400,
  lastPedestrianLedChangeTime = 0,

  buzzerState = LOW,
  lastBuzzerChangeTime = 0,
  buzzerCrossingTone = 500,
  buzzerBlinkingTone = 700,

  buzzerCrossingInterval = 800,
  buzzerBlinkingInterval = 400;

unsigned int globalState = 0;



void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  pinMode(carLedRed, OUTPUT);
  pinMode(carLedYellow, OUTPUT);
  pinMode(carLedGreen, OUTPUT);

  pinMode(pedestrianLedRed, OUTPUT);
  pinMode(pedestrianLedGreen, OUTPUT);

  setState(STATE_CARS_CROSSING);
  Serial.begin(9600);
}

int getButtonState() {

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        return STATE_BUTTON_PRESSED;
      }
    }
  }

  lastButtonState = reading;
  return STATE_BUTTON_RELEASED;
}

void setLedValues(bool carRedValue, bool carYellowValue, bool carGreenValue, bool pedestrianRedValue, bool pedestrianGreenValue) {

  digitalWrite(carLedRed, carRedValue);
  digitalWrite(carLedYellow, carYellowValue);
  digitalWrite(carLedGreen, carGreenValue);

  digitalWrite(pedestrianLedRed, pedestrianRedValue);
  digitalWrite(pedestrianLedGreen, pedestrianGreenValue);
}

void setState(int state) {

  globalState = state;

  switch (globalState) {

    case STATE_CARS_CROSSING:
      lastChangeTime = STATE_IDLE; // loop is completed, resetting to idle
      resetBuzzer();
      setLedValues(LOW, LOW, HIGH, HIGH, LOW);
      break;
  
    case STATE_YELLOW_LIGHT:
      lastChangeTime = millis();
      setLedValues(LOW, HIGH, LOW, HIGH, LOW);
      break;
  
    case STATE_PEDESTRIANS_CROSSING:
      lastChangeTime = millis();
      resetBuzzer();
      setLedValues(HIGH, LOW, LOW, LOW, HIGH);
      break;
  
    case STATE_PEDESTRIANS_BLINKING:
      lastChangeTime = millis();
      resetBuzzer();
      setLedValues(HIGH, LOW, LOW, LOW, HIGH);
      break;
  
    default:
      break;
  }
}

void playBuzzer(int buzzerTone) {

  if (buzzerState == HIGH) {
    tone(buzzerPin, buzzerTone);
  } else {
    noTone(buzzerPin);
  }
}

void resetBuzzer() {

  noTone(buzzerPin);
  buzzerState = LOW;
  lastBuzzerChangeTime = 0;
}

void setBuzzerState(int buzzerTone, int buzzerInterval) {

  if (currentTime - lastBuzzerChangeTime > buzzerInterval) {
    lastBuzzerChangeTime = currentTime;
    buzzerState = !buzzerState;
  }
  playBuzzer(buzzerTone);
}

void setGreenBlinkingLedState() {

  if (currentTime - lastPedestrianLedChangeTime > pedestrianLedBlinkingInterval) {
    lastPedestrianLedChangeTime = currentTime;
    pedestrianGreenLedState = !pedestrianGreenLedState;
  }

  setLedValues(HIGH, LOW, LOW, LOW, pedestrianGreenLedState);
}

void doStateAction() {

  switch (globalState) {

    case STATE_PEDESTRIANS_CROSSING:
      setBuzzerState(buzzerCrossingTone, buzzerCrossingInterval);
      break;
  
    case STATE_PEDESTRIANS_BLINKING:
      setBuzzerState(buzzerBlinkingTone, buzzerBlinkingInterval);
      setGreenBlinkingLedState();
      break;

    default:
      break;
  }
}

void determineState() {

  int buttonValue = getButtonState();
  currentTime = millis();

  if (globalState == STATE_CARS_CROSSING && lastChangeTime == STATE_IDLE && buttonValue == STATE_BUTTON_PRESSED) {
    lastChangeTime = millis();
  }

  if (lastChangeTime != STATE_IDLE) {

    if (globalState == STATE_CARS_CROSSING && currentTime - lastChangeTime > STATE_CARS_CROSSING_DURATION) {
      setState(STATE_YELLOW_LIGHT);
    }

    if (globalState == STATE_YELLOW_LIGHT && currentTime - lastChangeTime > STATE_YELLOW_LIGHT_DURATION) {
      setState(STATE_PEDESTRIANS_CROSSING);
    }

    if (globalState == STATE_PEDESTRIANS_CROSSING && currentTime - lastChangeTime > STATE_PEDESTRIANS_CROSSING_DURATION) {
      setState(STATE_PEDESTRIANS_BLINKING);
    }

    if (globalState == STATE_PEDESTRIANS_BLINKING && currentTime - lastChangeTime > STATE_PEDESTRIANS_BLINKING_DURATION) {
      setState(STATE_CARS_CROSSING);
    }
  }
}


void loop() {

  determineState();
  doStateAction();

}
