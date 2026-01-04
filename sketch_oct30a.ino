const int motorPin  = D9;
const int buttonPin = D7;

// ===== VIBRATION SETTINGS =====
int vibFreq = 25;      // Hz (LRA sweet spot ~170–200)
int vibPower = 100;     // 0–255 (strength)

// ===== INTERNAL STATE =====
bool motorOn = false;
bool lastButton = HIGH;

// timing
unsigned long lastMicros = 0;
bool motorState = false;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // -------- BUTTON TOGGLE --------
  bool currentButton = digitalRead(buttonPin);

  if (lastButton == HIGH && currentButton == LOW) {
    motorOn = !motorOn;     // TOGGLE
    delay(200);             // debounce (simple & works)
  }
  lastButton = currentButton;

  // -------- MOTOR CONTROL --------
  if (!motorOn) {
    digitalWrite(motorPin, LOW);
    return;
  }

  // ---- software PWM ----
  unsigned long period = 1000000UL / vibFreq;
  unsigned long onTime = (period * vibPower) / 255;

  unsigned long now = micros();

  if (motorState && (now - lastMicros >= onTime)) {
    motorState = false;
    lastMicros = now;
    digitalWrite(motorPin, LOW);
  }
  else if (!motorState && (now - lastMicros >= (period - onTime))) {
    motorState = true;
    lastMicros = now;
    digitalWrite(motorPin, HIGH);
  }
}
