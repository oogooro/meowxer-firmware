#pragma once
#include <Arduino.h>

#define NUM_OF_LEDS 5

void ledSetup();
void ledAnim();
void ledUpdate();
void ledSet(bool* states);
void ledSet(uint8_t led, bool state);
void ledSetBrightness(uint8_t brightness);