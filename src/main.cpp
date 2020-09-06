#include <Arduino.h>
#include <ButtonHandler.h>

#define BUTTON_PIN 9
#define BUTTON_PIN_2 8

void onClick();
void onClick_2();

ButtonHandler buttonHandler(BUTTON_PIN, onClick);
ButtonHandler buttonHandler_2(BUTTON_PIN_2, onClick_2);

void setup() {
  Serial.begin(9600);
  Serial.println("BEGIN");
  digitalWrite(9, HIGH);
}

void onClick() 
{
  Serial.println("Button 1 pressed");
}

void onClick_2() 
{
  Serial.println("Button 2 pressed");
}

void loop() {
  buttonHandler.tick();
  buttonHandler_2.tick();
} 