const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int buttonState = 0;
int ledcolor = 0;
bool ButtonPressed = false;
String currentcolor = "led";

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
  buttonState = digitalRead(buttonPin);
  Serial.print("Current Color: ");
  Serial.println(currentcolor);

  if(buttonState == HIGH && !ButtonPressed){
    ledcolor = ledcolor + 1;
    ButtonPressed = true;
    //delay(100);
  }

  if(buttonState == LOW && ButtonPressed){
    ButtonPressed = false;
  }

  if (ledcolor == 0){
    currentcolor = "LED off";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 1){
    //red
    currentcolor = "RED";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 2){
    //green
    currentcolor = "GREEN";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 3){
    //blue
    currentcolor = "BLUE";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }

  else if (ledcolor == 4){
    //yellow
    currentcolor = "YELLOW";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }

  else if (ledcolor == 5){
    //purple
    currentcolor = "PURPLE";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }

  else if (ledcolor == 6){
    //cyan
    currentcolor = "CYAN";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }

  else if (ledcolor == 7){
    //white
    currentcolor = "WHITE";
    digitalWrite(RledPin,LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }

  else if (ledcolor == 8){
    //blink
    currentcolor = "RAINBOW";
    //red
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(138);
    //green
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
    delay(138);
    //blue
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
    delay(138);
    //yellow
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
    delay(138);
    //purple
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
    delay(138);
    //cyan
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
    delay(138);
  }

  else if (ledcolor == 9){
    ledcolor = 0;
  }
}
