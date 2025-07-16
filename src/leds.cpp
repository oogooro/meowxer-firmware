#include "leds.h"

const uint8_t ledPins[NUM_OF_LEDS] = { PB0, PB1, PB10, PB11, PB8 };
bool ledStates[NUM_OF_LEDS]{ false };
uint8_t ledBrightness = 255;

void ledSetup() {
    for (const auto ledPin : ledPins) {
        pinMode(ledPin, OUTPUT);
        analogWrite(ledPin, 0);
    }

#ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
#endif
}

void ledAnim() {
    for (uint8_t i = 0; i < (NUM_OF_LEDS / 2) + 1; i++) {
        uint8_t pins[i == 0 ? 1 : 2] = {};
        if (i == 0) pins[0] = ledPins[(NUM_OF_LEDS / 2)];
        else {
            pins[0] = ledPins[(NUM_OF_LEDS / 2) + i];
            pins[1] = ledPins[(NUM_OF_LEDS / 2) - i];
        }

        for (uint8_t k = 0; k < 255; k++) {
            for (auto pin : pins) analogWrite(pin, k);
            delayMicroseconds((1 + (i * 2)) * 250);
        }
    }

    for (uint8_t i = 0; i < (NUM_OF_LEDS / 2) + 1; i++) {
        uint8_t pins[i == 0 ? 1 : 2] = {};
        if (i == 0) pins[0] = ledPins[(NUM_OF_LEDS / 2)];
        else {
            pins[0] = ledPins[(NUM_OF_LEDS / 2) + i];
            pins[1] = ledPins[(NUM_OF_LEDS / 2) - i];
        }

        for (uint8_t k = 255; k >= 0; k--) {
            for (auto pin : pins) analogWrite(pin, k);
            delayMicroseconds((1 + (i * 2)) * 250);
            if (k == 0) break; // we don't have negative numbers so we break here lol
        }
    }

    for (auto pin : ledPins) digitalWrite(pin, LOW);
}

void ledUpdate() {
    for (uint8_t i = 0; i < NUM_OF_LEDS; i++) {
        analogWrite(ledPins[i], ledStates[i] ? ledBrightness : 0);
    }
}

void ledSet(bool* states) {
    memcpy(ledStates, states, NUM_OF_LEDS);
    ledUpdate();
}

void ledSet(uint8_t led, bool state) {
    ledStates[led] = state;
    ledUpdate();
}

void ledSetBrightness(uint8_t brightness) {
    ledBrightness = brightness;
    ledUpdate();
}