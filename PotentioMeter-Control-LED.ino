const int RledPin = 3;
const int BledPin = 4;
const int GledPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);

  Serial.println(sensorValue);
  if(sensorValue < 255){
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  //
  else if(sensorValue < 511){
    digitalWrite(GledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  //
  else if(sensorValue < 767){
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  //
  else if(sensorValue < 1023){
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  delay(1);
}
