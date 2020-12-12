#include "Arduino.h"
#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(int pin, void(* onClick)())
{
    _pin = pin;
    _lastButtonState = LOW;
    _debounceDelay = 50;
    _lastDebounceTime = 0;
    _onClick = onClick;
    pinMode(pin, INPUT);
}

void ButtonHandler::tick()
{
    int reading = digitalRead(_pin);

    if (reading != _lastButtonState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        
        if (reading != _buttonState) {
            _buttonState = reading;
            if (_buttonState == HIGH) {
                //Button down
                _onClick();
            }
        }
    }
    _lastButtonState = reading;
}