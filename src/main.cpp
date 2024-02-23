#include <Arduino.h>

const int PIN_LED_RED = 4;    // The Number of the red LED pin.
const int PIN_LED_GREEN = 5;  // The Number of the green LED pin.
const int PIN_LED_BLUE = 6;   // The Number of the blue LED pin.
const int PIN_LED_YELLOW = 7; // The Number of the yellow LED pin.
const int PIN_BUTTON_1 = 8;   // The number of the button 1 (KEY1) pin.
const int PIN_BUTTON_2 = 9;   // The number of the button 2 (KEY2) pin.

int buttonState_1 = 0; // Keep track of the button 1 state.
int buttonState_2 = 0; // Keep track of the button 2 state.
int count = 0;
int leavingCount = 0;
byte prevButtonOneState = HIGH;
byte prevButtonTwoState = HIGH;

void buttonEnterHandler(int BUTTON_PIN, int LED_PIN) {
  const int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == prevButtonOneState) return;

  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    count++;
    delay(100);
    Serial.println("Entering: "  + String(count));
    digitalWrite(LED_PIN, LOW);
  } 

  prevButtonOneState = buttonState;
}

void buttonLeaveHandler(int BUTTON_PIN, int LED_PIN) {
  const int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == prevButtonTwoState) return;

  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    leavingCount++;
    delay(100);
    Serial.println("Leaving: "  + String(leavingCount));
    digitalWrite(LED_PIN, LOW);
  } 

  prevButtonTwoState = buttonState;
}

void setup() {
  Serial.begin(9600);


  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);
}

void loop() {
  buttonEnterHandler(PIN_BUTTON_1, PIN_LED_BLUE);
  buttonLeaveHandler(PIN_BUTTON_2, PIN_LED_RED);
}