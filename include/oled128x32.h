#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

extern Adafruit_SSD1306 display;

bool initOled();
void drawVolume(uint8_t volume);
void drawMute(uint8_t channel, bool unmute);
void clearOled();
void setOledBrightness(uint8_t brightness);