#pragma once
#include <Arduino.h>

#define NUM_OF_BUTTONS 5
#define DEBOUNCE_DELAY 50
#define LONGPRESS_TIME 3000

extern uint8_t pressedButtons;

void buttonsSetup();
bool readButtons();
uint8_t readLongpress();