
#include "Keyboard.h"
#include "Mouse.h"

// Number of buttons to handle
const int InputCount = 3;

// Arduino PINs to use
const int pins[InputCount] = {
    2,
    3,
    5
};

const int rockerPin = 1;

// Keys to send (order has to match the pins array)
const byte keys[InputCount] = {
    KEY_DOWN_ARROW,
    KEY_LEFT_ARROW,
    KEY_RIGHT_ARROW
    
};

// Debounce delay
const long debounceDelay = 1000;

bool status[InputCount] = {LOW};
bool rockerStatus = LOW;

long lastDebounces[InputCount] = {0};
long rockerDebounce = 0;         // the last time the output pin was toggled

void setup() {
    for (int i = 0; i < InputCount; ++i) {
        pinMode(pins[i], INPUT);
    }

    pinMode(rockerPin, INPUT);

    Keyboard.begin();
}

void loop() {
   
    // Handles the three buttons. Could use rework to handle PWM on 0, 1, 2
    for (int i = 0; i < InputCount; ++i) {
        const int pinStatus = digitalRead(pins[i]);
        if (pinStatus != status[i] && millis() - debounceDelay > lastDebounces[i]) {
            if (pinStatus != status[i])
            {
              Serial.print("Current Pin: ");
              Serial.print(i);
              Serial.print("\t");
              Serial.print("Pin Status :");
              Serial.print(pinStatus);
              Serial.print("\t");
              Serial.print("Saved Status :");
              Serial.print(status[i]);
              Serial.print("\n");
              
              status[i] = pinStatus;
              if (pinStatus == HIGH) {
                  status[i] = HIGH;
                  Keyboard.press(keys[i]);
                  Keyboard.releaseAll();
              }
              else
              {
                status[i] = LOW;
              }
            }           
            lastDebounces[InputCount] = millis();
        }
    }

    const int rockerPinStatus = digitalRead(rockerPin);
    if (rockerPinStatus != rockerStatus && millis() - rockerDebounce > debounceDelay) {
      rockerStatus = rockerPinStatus;
      
      if (rockerPinStatus == HIGH)
        Keyboard.press('B');
      else
        Keyboard.press('A');
       
        
      Keyboard.releaseAll();
      rockerDebounce = millis();    
    }
    
    delay(200);
}
