#include <Encoder.h>

// Encoder 
Encoder myEncoder(2, 3);
int btnPin = 4;
int btnState;
int encoderVal = 0;
bool minmax;

// RGB 
int greenPin = 10;
int redPin = 11;
int bluePin = 9;
int colourState;

// Buzzer
int buzzerPin = 13;


void setup() {
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  moduleReset();
  minmax = false;
  encoderVal = myEncoder.read();

  maintainVal(encoderVal, minmax);
  colourState = colourStateChange(encoderVal);
  btnState = digitalRead(btnPin);
  Serial.println("Colour option: " + String(colourState));
  
  if(btnState == LOW){
    Serial.println("PRESSED");
    colourOutput(colourState);
    tone(buzzerPin, 375);
    delay(5000);
  }
  delay(500);
}

void maintainVal(int val, bool minmax){
    if (val >= 600 && !minmax){
      encoderVal = 600;
      Serial.println("Please rotate back! Maximum value reached!");
    } else if (val < 0 && !minmax){
      encoderVal = 0;
      Serial.println("Please rotate back! Minimum value reached!");
    }
    minmax = true;
  }

void setColor(int green, int red, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

int colourStateChange(int encoderVal){
  int num = 0;

  if (encoderVal >= 0 && encoderVal <= 100){
    num = 1;
  } else if (encoderVal > 100 && encoderVal <= 200){
    num = 2;
  } else if (encoderVal > 200 && encoderVal <= 300){
    num = 3;
  } else if (encoderVal > 300 && encoderVal <= 400){
    num = 4;
  } else if (encoderVal > 400 && encoderVal <= 500){
    num = 5;
  } else if (encoderVal > 500 && encoderVal <= 600){
    num = 6;
  } else {
    num = 0;
  }
  return num;
}

int colourOutput (int colourState){
  switch (colourState){
    case 1:
      setColor(255, 0, 0);
      tone(buzzerPin, 500);
      break;
    case 2:
      setColor(0, 255, 0);
      tone(buzzerPin, 475);
      break;
    case 3:
      setColor(0, 0, 255);
       tone(buzzerPin, 450);
      break;
    case 4:
      setColor(255, 255, 0);
      tone(buzzerPin, 425);
      break;
    case 5:
      setColor(0, 255, 255);
      tone(buzzerPin, 400);
      break;
    case 6:
      setColor(255, 0, 255);
      tone(buzzerPin, 375);
      break;
  }
}

void moduleReset(){
  setColor(0,0,0);
  noTone(buzzerPin);
}
