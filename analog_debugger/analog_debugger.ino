
#include "Keyboard.h"
#include "Mouse.h"

// Number of buttons to handle
const int InputCount = 3;

// Arduino PINs to useB
const int pins[InputCount] = {
    2,
    3,
    5
};

const int rockerPin = 1;

// Keys to send (order has to match the pins array)
const byte keys[InputCount][3] = {
    {KEY_RIGHT_ALT, KEY_RIGHT_GUI, 'r'},
    {KEY_F8},
    {KEY_F7}
};

const long debounceDelay = 100;

bool status[InputCount] = {LOW};
bool rockerStatus = LOW;

long lastDebounces[InputCount] = {0};
long rockerDebounce = 0;

void setup() {
    for (int i = 0; i < InputCount; ++i) {
        pinMode(pins[i], INPUT);
    }
    pinMode(rockerPin, INPUT);
    
    Keyboard.begin();
}

void loop() {
   
    for (int i = 0; i < InputCount; ++i) {
      
      const int pinStatus = digitalRead(pins[i]);

      if (pinStatus != status[i] && millis() - debounceDelay > lastDebounces[i]) {
        if (pinStatus != status[i])
        {            
          if (pinStatus == HIGH) 
          {
              for (int k = 0; k < sizeof(keys[i])/sizeof(byte); ++k)
              {
                Serial.print(k);
                Serial.print("\n");
                Keyboard.press(keys[i][k]);
              }
              delay(100);
           }
           Keyboard.releaseAll();
         }
         status[i] = pinStatus;
      }           
      lastDebounces[i] = millis();
    }

    const int rockerPinStatus = map(digitalRead(rockerPin), LOW, HIGH, LOW, HIGH); 
    if (rockerPinStatus != rockerStatus && millis() - rockerDebounce > debounceDelay) {               
      if (rockerPinStatus == HIGH)
      {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('d');
      }
      else
      {
        Keyboard.press(KEY_RIGHT_GUI);
        Keyboard.press(KEY_F2);        
      }
      delay(100);
      Keyboard.releaseAll();
        
      rockerStatus = rockerPinStatus;
      rockerDebounce = millis();    
    }
    delay(200);
}

