const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;
const int buttonPin = 5;

const bool COMMON_ANODE = true;          // LED turns on with LOW
const bool BUTTON_ACTIVE_HIGH = false;   // button reads LOW when pressed

int mood = 0;
const int neutralMood = 10;

bool ButtonPressed = false;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
const long unTouchInterval = 5000;
const long reducedInterval = 1000;

// blinking settings
const unsigned long redWaitTime = 3000;      // 3 s at red before blinking starts
const unsigned long slowBlinkInterval = 500; // red blink speed (ms on / ms off)
const unsigned long fastBlinkInterval = 100; // blue blink speed (ms on / ms off)
bool atRed = false;
unsigned long redStartTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, BUTTON_ACTIVE_HIGH ? INPUT : INPUT_PULLUP);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  mood = neutralMood;
  touchedTimer = millis();
  reducedTimer = millis();
}

void loop() {
  unsigned long now = millis();

  // --- track how long the toy has been at red ---
  if (mood == 0 && !atRed) {
    atRed = true;
    redStartTime = now;
  }
  if (mood != 0) {
    atRed = false;
  }

  // --- show the LED (steady or blinking) ---
  unsigned long blinkInterval = 0;
  if (mood == 20) {
    blinkInterval = fastBlinkInterval;                       // blue: fast blink
  } else if (mood == 0 && now - redStartTime >= redWaitTime) {
    blinkInterval = slowBlinkInterval;                       // red after 3 s: blink
  }

  if (blinkInterval > 0) {
    bool ledOn = ((now / blinkInterval) % 2 == 0);
    if (ledOn) {
      showLEDState(mood);
    } else {
      setLED(0, 0, 0);   // off
    }
  } else {
    showLEDState(mood);  // steady color
  }

  // --- button ---
  bool pressed = (digitalRead(buttonPin) == (BUTTON_ACTIVE_HIGH ? HIGH : LOW));

  if (pressed && !ButtonPressed) {
    mood = mood + 1;
    if (mood > 20) mood = 20;
    touchedTimer = millis();
    ButtonPressed = true;
    Serial.println(mood);
    delay(30);   // debounce
  }
  if (!pressed && ButtonPressed) {
    ButtonPressed = false;
    delay(30);   // debounce
  }

  // --- idle decay ---
  unsigned long currentTimer = millis();
  if (currentTimer - touchedTimer > unTouchInterval) {
    if (currentTimer - reducedTimer > reducedInterval) {
      mood = mood - 1;
      if (mood < 0) mood = 0;
      reducedTimer = currentTimer;
      Serial.println(mood);
    }
  }
}

void setLED(int r, int g, int b) {
  if (COMMON_ANODE) {
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  }
  analogWrite(RledPin, r);
  analogWrite(GledPin, g);
  analogWrite(BledPin, b);
}

void showLEDState(int state) {
  float step = 255 / 10.0;
  if (state >= neutralMood) {
    // neutral (green) -> happy (blue)
    setLED(0, 255 - step * (state - neutralMood), step * (state - neutralMood));
  } else {
    // neutral (green) -> sad (red)
    setLED(step * (neutralMood - state), 255 - step * (neutralMood - state), 0);
  }
}