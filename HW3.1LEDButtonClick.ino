const int buttonPin = 2;
const int redPin = 3;     // D3
const int greenPin = 5;
const int bluePin = 6;

// Blink half-periods (ms the LED stays on, then off)
const unsigned long SLOW_INTERVAL = 1000;
const unsigned long MEDIUM_INTERVAL = 500;
const unsigned long FAST_INTERVAL = 150;

int mode = 0;                       // 0 steady, 1 slow, 2 medium, 3 fast
int lastButtonState = LOW;
bool ledOn = true;
unsigned long lastToggle = 0;
unsigned long lastPress = 0;

void setColor(bool on) {
  // Red only. For white light, also write greenPin and bluePin.
  digitalWrite(redPin, on ? HIGH : LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  setColor(true);                   // initial state: steady on
}

void loop() {
  // 1. Detect a new button press (with debounce)
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && lastButtonState == LOW && millis() - lastPress > 50) {
    mode = (mode + 1) % 4;          // 0 -> 1 -> 2 -> 3 -> back to 0
    lastPress = millis();
    ledOn = true;                   // restart each mode with the LED on
    setColor(true);
    lastToggle = millis();
  }
  lastButtonState = buttonState;

  // 2. Run the current mode
  unsigned long interval = 0;
  switch (mode) {
    case 0: setColor(true); return;           // steady: nothing to toggle
    case 1: interval = SLOW_INTERVAL;   break;
    case 2: interval = MEDIUM_INTERVAL; break;
    case 3: interval = FAST_INTERVAL;   break;
  }

  if (millis() - lastToggle >= interval) {
    ledOn = !ledOn;
    setColor(ledOn);
    lastToggle = millis();
  }
}