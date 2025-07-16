#include "buttons.h"

const uint8_t buttonPins[NUM_OF_BUTTONS] = { PA15, PA10, PA9, PA8, PB15 };

unsigned long buttonsUpdatedTimestamp = millis();
uint8_t pressedButtons = 0;

void buttonsSetup() {
    for (const auto buttonPin : buttonPins) {
        pinMode(buttonPin, INPUT_PULLUP);
    }
}

bool readButtons() {
    if (millis() - buttonsUpdatedTimestamp >= DEBOUNCE_DELAY) {
        uint32_t pressed = 0;
        for (uint8_t i = 0; i < NUM_OF_BUTTONS; i++) {
            if (!digitalRead(buttonPins[i])) pressed |= 1 << i;
        }

        if (pressed != pressedButtons) {
            pressedButtons = pressed;
            buttonsUpdatedTimestamp = millis();
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}