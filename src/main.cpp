#include <Arduino.h>
#include <ButtonHandler.h>

#define MENU_BUTTON_PIN 6
#define BUTTON_1_PIN 7
#define BUTTON_2_PIN 8
#define BUTTON_3_PIN 9

#define LED_A 10
#define LED_B 16
#define LED_1 14
#define LED_2 15
#define LED_3 4

void menuButtonPressed();
void button1Pressed();
void button2Pressed();
void button3Pressed();
void sendMidi();

ButtonHandler buttonHandlerMenu(MENU_BUTTON_PIN, menuButtonPressed);
ButtonHandler buttonHandler_1(BUTTON_1_PIN, button1Pressed);
ButtonHandler buttonHandler_2(BUTTON_2_PIN, button2Pressed);
ButtonHandler buttonHandler_3(BUTTON_3_PIN, button3Pressed);

bool active_menu_led = true; // true = A, false = B
int active_led = LED_1;

void setup() {
  Serial.begin(9600);
  sendMidi();

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
}

void menuButtonPressed() {
  active_menu_led = !active_menu_led;
  sendMidi();
}

void button1Pressed() {
  active_led = LED_1;
  sendMidi();
}

void button2Pressed() {
  active_led = LED_2;
  sendMidi();
}

void button3Pressed() {
  active_led = LED_3;
  sendMidi();
}

void updateLeds() {
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);

  digitalWrite(active_led, HIGH);
  if (active_menu_led) {
    digitalWrite(LED_A, HIGH);
  } else {
    digitalWrite(LED_B, HIGH);
  }
}

void sendMidi() {
  if (active_menu_led) {
    Serial.println("MODE_A");
  } else {
    Serial.println("MODE_B");
  }

  if (active_led == LED_1) {
    Serial.println("PROFILE_1 ON");
  } else {
    Serial.println("PROFILE_1 OFF");
  }

  if (active_led == LED_2) {
    Serial.println("PROFILE_2 ON");
  } else {
    Serial.println("PROFILE_2 OFF");
  }

  if (active_led == LED_3) {
    Serial.println("PROFILE_3 ON");
  } else {
    Serial.println("PROFILE_3 OFF");
  }
}

void loop() {
  updateLeds();

  buttonHandlerMenu.tick();
  buttonHandler_1.tick();
  buttonHandler_2.tick();
  buttonHandler_3.tick();
}