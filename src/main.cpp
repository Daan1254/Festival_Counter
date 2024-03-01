#include <Arduino.h>

const int PIN_LED_RED = 4;    // The Number of the red LED pin.
const int PIN_LED_GREEN = 5;  // The Number of the green LED pin.
const int PIN_LED_BLUE = 6;   // The Number of the blue LED pin.
const int PIN_LED_YELLOW = 7; // The Number of the yellow LED pin.
const int PIN_BUTTON_1 = 8;   // The number of the button 1 (KEY1) pin.
const int PIN_BUTTON_2 = 9;   // The number of the button 2 (KEY2) pin.
int ledOrder[] = {PIN_LED_RED, PIN_LED_GREEN, PIN_LED_BLUE};
int prevOrderIndex = 0;
int currentOrderIndex = 2;

int buttonState_1 = 0; // Keep track of the button 1 state.
int buttonState_2 = 0; // Keep track of the button 2 state.
int maxVisitors = 10;
int count = 0;
byte prevButtonOneState = HIGH;
byte prevButtonTwoState = HIGH;
unsigned long previousMillis = 0;
const long interval = 100;  // interval at which to blink (milliseconds)

void toggleLED() {
   
    prevOrderIndex = currentOrderIndex;
    if (currentOrderIndex == 2) {
        currentOrderIndex = 0;
    } else {
        currentOrderIndex++;
    } 
    delay(100);
    digitalWrite(ledOrder[prevOrderIndex], LOW);
    digitalWrite(ledOrder[currentOrderIndex], HIGH);
}

void buttonEnterHandler(int BUTTON_PIN, int LED_PIN) {
    unsigned long currentMillis = millis();

    

    const int buttonState = digitalRead(BUTTON_PIN);
    previousMillis = currentMillis;
    if (buttonState == prevButtonOneState) return;

    if (buttonState == LOW) {
        if (count >= maxVisitors) {
            int loopItterations = 0;
            while (loopItterations < 3) 
            {
                digitalWrite(PIN_LED_RED, HIGH);
                delay(250);
                digitalWrite(PIN_LED_RED, LOW);
                delay(250);
                loopItterations++;
            }
        
            Serial.println("Maximum visitors reached");
            return;
        }
        toggleLED();
        count++;
        Serial.println("Total Festival Visitors: "  + String(count));
    } 

    prevButtonOneState = buttonState;
}

void buttonLeaveHandler(int BUTTON_PIN, int LED_PIN) {
    unsigned long currentMillis = millis();

    const int buttonState = digitalRead(BUTTON_PIN);
    previousMillis = currentMillis;
    if (buttonState == prevButtonTwoState) return;

    if (buttonState == LOW) {
        if (count <= 0) {
          Serial.println("Visitor Count will go under 0. Not possible");
          return;
        }
        count--;
        delay(100);
        Serial.println("Total Festival Visitors: "  + String(count));


        if (currentOrderIndex == 0) {
            prevOrderIndex = currentOrderIndex;
            currentOrderIndex = 2;
        } else {
            prevOrderIndex = currentOrderIndex;
            currentOrderIndex--;
        }
        
        delay(100);
        Serial.println("CurrentorderIndex: "  + String(currentOrderIndex));
        Serial.println("prevOrderIndex: "  + String(prevOrderIndex));
        digitalWrite(ledOrder[prevOrderIndex], LOW);
        digitalWrite(ledOrder[currentOrderIndex], HIGH);
    }

    prevButtonTwoState = buttonState;
}

void setup() {
    Serial.begin(9600);

    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_BLUE, OUTPUT);
    pinMode(PIN_BUTTON_1, INPUT_PULLUP);
    pinMode(PIN_BUTTON_2, INPUT_PULLUP);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        buttonEnterHandler(PIN_BUTTON_1, PIN_LED_BLUE);
        buttonLeaveHandler(PIN_BUTTON_2, PIN_LED_YELLOW);
    }
}
