const int buttonPin = 2;
const int RLedPin = 9;
const int GLedPin = 10;
const int BLedPin = 11;

int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000;

int lightNum = 0;
int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;

int RCurrentColor = 0;
int GCurrentColor = 0;
int BCurrentColor = 0;

int currentMode = 0;

unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn = true;

const int fadeAmount = 2;
int fadeDirection = 1;

void setup() 
{
  pinMode(buttonPin, INPUT);
  pinMode(RLedPin, OUTPUT);
  pinMode(GLedPin, OUTPUT);
  pinMode(BLedPin, OUTPUT);
}

void loop() 
{
  checkButton();
  updateLEDColor();
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor);
}

void checkButton()
{
  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH && !buttonPressed){
    pressingTime = millis();
    buttonPressed = true;
  }
  if(buttonState == LOW && buttonPressed){
    unsigned long currentTime = millis();
    if(currentTime - pressingTime < longPressInterval){
      //short click
      changeLEDColor();
    }
    else{
      //long press
      changeMode();
    }
    buttonPressed = false;
  }
}

void setRGBLEDColor(int r, int g, int b){
  analogWrite(RLedPin, r);
  analogWrite(GLedPin, g);
  analogWrite(BLedPin, b);
}

void changeLEDColor(){

  lightNum = lightNum + 1;
  if(lightNum >= 6)
    lightNum = 0;

  if(lightNum == 0){
    //white
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 0;
  }

  if(lightNum == 1){
    //red
    RLightColor = 0;
    GLightColor = 255;
    BLightColor = 255;
  }

  if(lightNum == 2){
    //green
    RLightColor = 255;
    GLightColor = 0;
    BLightColor = 255;
  }

  if(lightNum == 3){
    //blue
    RLightColor = 255;
    GLightColor = 255;
    BLightColor = 0;
  }

  if(lightNum == 4){
    //yellow
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 255;
  }

  if(lightNum == 5){
    //purple
    RLightColor = 0;
    GLightColor = 255;
    BLightColor = 0;
  }

  if(lightNum == 6){
    //cyan
    RLightColor = 255;
    GLightColor = 0;
    BLightColor = 0;
  }

  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;
}

void changeMode(){
  currentMode = currentMode + 1;
  if (currentMode >= 3){
    currentMode = 0;
  }

  if (currentMode == 1){
    blinkTimer = 0;
    blinkOn = true;
  }

  if(currentMode == 2){
    fadeDirection = 1;
  }
}

void updateLEDColor(){
  if(currentMode == 0){
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }
  else if(currentMode == 1){
    unsigned long currentTime = millis();
    if(currentTime - blinkTimer > blinkInterval){
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }
    if(blinkOn){
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    }
    else{
      RCurrentColor = 255;
      GCurrentColor = 255;
      BCurrentColor = 255;
    }
  }
  else if (currentMode == 2){
    //breathing light mode
    if(RLightColor > 0)
      RCurrentColor = RCurrentColor + fadeDirection * fadeAmount;
    if(GLightColor > 0)
      GCurrentColor = GCurrentColor + fadeDirection * fadeAmount;
    if(BLightColor > 0)
      BCurrentColor = BCurrentColor + fadeDirection * fadeAmount;

    if(RCurrentColor > RLightColor || GCurrentColor > GLightColor || BCurrentColor > BLightColor){
      fadeDirection = -fadeDirection;
    }
    else if (RCurrentColor < 0 || GCurrentColor < 0 || BCurrentColor < 0){
      fadeDirection = -fadeDirection;
    }
  }
}