#pragma once
#include <Arduino.h>

#define NUM_OF_BUTTONS 5
#define DEBOUNCE_DELAY 50

extern uint8_t pressedButtons;

void buttonsSetup();
bool readButtons();