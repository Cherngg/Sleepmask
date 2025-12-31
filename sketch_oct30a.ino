const int motorPin  = D9;
const int buttonPin = D7;

bool motorOn = false;
bool lastButton = HIGH;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool currentButton = digitalRead(buttonPin);

  if (lastButton == HIGH && currentButton == LOW) {
    motorOn = !motorOn;       
    delay(200);                
  }

  lastButton = currentButton;

  if (motorOn) {
    digitalWrite(motorPin, HIGH);
  } else {
    digitalWrite(motorPin, LOW);
  }
}
