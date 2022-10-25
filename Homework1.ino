const int redPotPin = A2,
          greenPotPin = A1,
          bluePotPin = A0;

const int redPin = 3,
          greenPin = 5,
          bluePin = 6;

const int potLowerBound = 0,
          potUpperBound = 1023,
          ledLowerBound = 0,
          ledUpperBound = 255;
         
int redPotVal = 0,
    greenPotVal = 0,
    bluePotVal = 0,
    
    redPinVal = 0,
    greenPinVal = 0,
    bluePinVal = 0;

void setup() {
  pinMode(redPotPin, INPUT);
  pinMode(greenPotPin, INPUT);
  pinMode(bluePotPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // potentiometer data
  redPotVal = analogRead(redPotPin);
  greenPotVal = analogRead(greenPotPin);
  bluePotVal = analogRead(bluePotPin);

  // get the mapped value
  redPinVal = map(redPotVal, potLowerBound, potUpperBound, ledLowerBound, ledUpperBound);
  greenPinVal = map(greenPotVal, potLowerBound, potUpperBound, ledLowerBound, ledUpperBound);
  bluePinVal = map(bluePotVal, potLowerBound, potUpperBound, ledLowerBound, ledUpperBound);

  // write data
  analogWrite(redPin, redPinVal);
  analogWrite(greenPin, greenPinVal);
  analogWrite(bluePin, bluePinVal);

  delay(1);
  
}
