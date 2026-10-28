const int buttonPin = 2;
const int RledPin = 3;
const int BledPin = 4;
const int GledPin = 5;

int buttonState = 0;
int ledState = LOW;
bool ButtonPressed = false;

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
const long interval = 1000;
const long Gametime = 5000;
const long result = 3000;
bool Gamestart = false;
int hits = 0;
int color = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis();
  buttonState = digitalRead(buttonPin);

  if(Gamestart == false){
    if (currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      if (ledState == LOW){
        ledState = HIGH;
      }
      else {
        ledState = LOW;
      }
    }
    if (color == 1){
      if (ledState == LOW){
        digitalWrite(RledPin, LOW);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, HIGH);
      }
      else {
        digitalWrite(RledPin, HIGH);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, HIGH);
      }
    }
    //
    else if (color == 2){
      if (ledState == LOW){
        digitalWrite(RledPin, HIGH);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, LOW);
      }
      else {
        digitalWrite(RledPin, HIGH);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, HIGH);
      }
    }
    //
    else if (color == 3){
      if (ledState == LOW){
        digitalWrite(RledPin, HIGH);
        digitalWrite(GledPin, LOW);
        digitalWrite(BledPin, HIGH);
      }
      else {
        digitalWrite(RledPin, HIGH);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, HIGH);
      }
    }
    //
    else if (color == 0){
      if (ledState == LOW){
        digitalWrite(RledPin, LOW);
        digitalWrite(GledPin, LOW);
        digitalWrite(BledPin, LOW);
      }
      else {
        digitalWrite(RledPin, HIGH);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, HIGH);
      }
    }
    //
    if(buttonState == HIGH && !ButtonPressed){
      ButtonPressed = true;
    }
    else if(buttonState == LOW && ButtonPressed){
      ButtonPressed = false;
      previousMillis = currentMillis;
      hits = 0;
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
      Gamestart = true;
    }
  }
  //
  else if (Gamestart == true){
    if (currentMillis - previousMillis >= Gametime){
      if (currentMillis2 - previousMillis2 >= result) {
        Gamestart = false;
      }
      else{
        digitalWrite(RledPin, LOW);
        digitalWrite(GledPin, LOW);
        digitalWrite(BledPin, LOW);
        if (hits<= 10){
          color = 1;
        }
        else if (10 < hits && hits <= 20){
          color = 2;
        }
        else if (hits >20){
          color = 3;
        }
      }
    }
    else {
      previousMillis2 = currentMillis2;
      if(buttonState == HIGH && ButtonPressed == false) {
        ButtonPressed = true;
        hits = hits + 1;
        Serial.println(hits);
        digitalWrite(RledPin, LOW);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, HIGH);
      }
      else if (buttonState == LOW && ButtonPressed == true){
        ButtonPressed = false;
        digitalWrite(RledPin, HIGH);
        digitalWrite(GledPin, HIGH);
        digitalWrite(BledPin, HIGH);
      }
    }
  }
}
