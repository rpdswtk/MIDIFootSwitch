#include <Arduino.h>
#include <ButtonHandler.h>
#include "MIDIUSB.h"

#define MENU_BUTTON_PIN 6
#define BUTTON_1_PIN 7
#define BUTTON_2_PIN 8
#define BUTTON_3_PIN 9

#define LED_A 10
#define LED_B 16
#define LED_1 14
#define LED_2 15
#define LED_3 4

#define CONTROL_CHANGE_EVENT_TYPE 0x0B
#define MIDI_CHANNEL 0

void menuButtonPressed();
void button1Pressed();
void button2Pressed();
void button3Pressed();
void sendMidi();
void sendControlChange(byte channel, byte value);

ButtonHandler buttonHandlerMenu(MENU_BUTTON_PIN, menuButtonPressed);
ButtonHandler buttonHandler_1(BUTTON_1_PIN, button1Pressed);
ButtonHandler buttonHandler_2(BUTTON_2_PIN, button2Pressed);
ButtonHandler buttonHandler_3(BUTTON_3_PIN, button3Pressed);

bool active_menu_led = true; // true = A, false = B
int active_led = LED_1;

void setup() {
  Serial.begin(115200);
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
  byte offset = 0;
  if (!active_menu_led) {
    offset = 1;
  }

  switch (active_led)
  {
    case LED_1:
      sendControlChange(MIDI_CHANNEL, 20 + offset);
    break;
    case LED_2:
      sendControlChange(MIDI_CHANNEL, 22 + offset);
    break;
    case LED_3:
      sendControlChange(MIDI_CHANNEL, 24 + offset);
    break;
  }
}

void sendControlChange(byte channel, byte value) {
  midiEventPacket_t event = { CONTROL_CHANGE_EVENT_TYPE, 0xB0 | channel, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

void loop() {
  updateLeds();
  buttonHandlerMenu.tick();
  buttonHandler_1.tick();
  buttonHandler_2.tick();
  buttonHandler_3.tick();
  MidiUSB.flush();
}