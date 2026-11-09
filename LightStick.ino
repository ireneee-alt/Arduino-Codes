const int buttonPin = 2;
const int RLedPin = 9;
const int GLedPin = 10;
const int BLedPin = 11;

const bool COMMON_ANODE = true;   // your LED: 0 = on, 255 = off

// ---- Button wiring ----
// Button between pin 2 and GND (no resistor): leave as is.
// Button between pin 2 and 5V with a pull-down resistor: set PRESSED to HIGH,
// RELEASED to LOW, and change INPUT_PULLUP to INPUT in setup().
const int PRESSED = LOW;
const int RELEASED = HIGH;

// Button
const unsigned long debounceTime = 30;
const unsigned long longPressInterval = 2000;   // 2 seconds or more = long press
const unsigned long doubleClickInterval = 300;  // max gap between two clicks
int lastReading = RELEASED;
int stableState = RELEASED;
unsigned long lastDebounceTime = 0;
unsigned long pressingTime = 0;
bool longPressHandled = false;

// Click counting
int clickCount = 0;
unsigned long lastClickTime = 0;

// Colors in normal form: 255 = fully on
const int NUM_COLORS = 7;
const int colors[NUM_COLORS][3] = {
  {255, 255, 255},  // white
  {255, 0,   0},    // red
  {0,   255, 0},    // green
  {0,   0,   255},  // blue
  {255, 255, 0},    // yellow
  {255, 0,   255},  // purple
  {0,   255, 255}   // cyan
};
int lightNum = 0;

// Rainbow
bool rainbowOn = false;
const unsigned long rainbowPeriod = 4000;  // ms for one full color cycle

// Modes: 0 = constant, 1 = blink, 2 = breathing
int currentMode = 0;
int brightness = 255;   // 0 - 255

// Blink
unsigned long blinkTimer = 0;
const unsigned long blinkInterval = 500;
bool blinkOn = true;

// Breathing
unsigned long fadeTimer = 0;
const unsigned long fadeInterval = 20;  // ms between steps
const int fadeAmount = 5;               // brightness change per step
int fadeDirection = -1;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(RLedPin, OUTPUT);
  pinMode(GLedPin, OUTPUT);
  pinMode(BLedPin, OUTPUT);
}

void loop()
{
  checkButton();
  updateBrightness();
  showColor();
}

void checkButton()
{
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();
    lastReading = reading;
  }

  if (millis() - lastDebounceTime > debounceTime && reading != stableState) {
    stableState = reading;

    if (stableState == PRESSED) {
      pressingTime = millis();
      longPressHandled = false;
    }
    else {
      // released: if the long press already fired, ignore; otherwise it was a short click
      if (!longPressHandled) {
        clickCount++;
        lastClickTime = millis();
      }
    }
  }

  // long press fires once the button has been held for 2 seconds
  if (stableState == PRESSED && !longPressHandled &&
      millis() - pressingTime >= longPressInterval) {
    changeMode();
    longPressHandled = true;
    clickCount = 0;
  }

  // Decide what the clicks mean (only while the button is up)
  if (clickCount > 0 && stableState == RELEASED) {
    if (clickCount >= 2) {
      toggleRainbow();              // double click: rainbow on/off only
      clickCount = 0;
    }
    else if (millis() - lastClickTime > doubleClickInterval) {
      changeLEDColor();             // single click: change color only
      clickCount = 0;
    }
  }
}

void changeLEDColor()
{
  lightNum = (lightNum + 1) % NUM_COLORS;
}

void toggleRainbow()
{
  rainbowOn = !rainbowOn;
}

void changeMode()
{
  currentMode = (currentMode + 1) % 3;

  if (currentMode == 1) {
    blinkTimer = millis();
    blinkOn = true;
  }
  if (currentMode == 2) {
    brightness = 255;
    fadeDirection = -1;
    fadeTimer = millis();
  }
}

void updateBrightness()
{
  if (currentMode == 0) {
    brightness = 255;
  }
  else if (currentMode == 1) {
    if (millis() - blinkTimer >= blinkInterval) {
      blinkOn = !blinkOn;
      blinkTimer = millis();
    }
    brightness = blinkOn ? 255 : 0;
  }
  else {
    // breathing
    if (millis() - fadeTimer >= fadeInterval) {
      fadeTimer = millis();
      brightness += fadeDirection * fadeAmount;

      if (brightness >= 255) {
        brightness = 255;
        fadeDirection = -1;
      }
      else if (brightness <= 0) {
        brightness = 0;
        fadeDirection = 1;
      }
    }
  }
}

// Convert a hue (0 - 360) to a full-brightness RGB color
void hueToRGB(float hue, int &r, int &g, int &b)
{
  float h = hue / 60.0;
  int sector = (int)h % 6;
  float f = h - (int)h;
  int q = 255 * (1.0 - f);
  int t = 255 * f;

  switch (sector) {
    case 0: r = 255; g = t;   b = 0;   break;
    case 1: r = q;   g = 255; b = 0;   break;
    case 2: r = 0;   g = 255; b = t;   break;
    case 3: r = 0;   g = q;   b = 255; break;
    case 4: r = t;   g = 0;   b = 255; break;
    default: r = 255; g = 0;  b = q;   break;
  }
}

void showColor()
{
  int r, g, b;

  if (rainbowOn) {
    float hue = (millis() % rainbowPeriod) * 360.0 / rainbowPeriod;
    hueToRGB(hue, r, g, b);
  }
  else {
    r = colors[lightNum][0];
    g = colors[lightNum][1];
    b = colors[lightNum][2];
  }

  // apply brightness (used by blink and breathing)
  r = (long)r * brightness / 255;
  g = (long)g * brightness / 255;
  b = (long)b * brightness / 255;

  setRGBLEDColor(r, g, b);
}

void setRGBLEDColor(int r, int g, int b)
{
  if (COMMON_ANODE) {
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  }
  analogWrite(RLedPin, r);
  analogWrite(GLedPin, g);
  analogWrite(BLedPin, b);
}