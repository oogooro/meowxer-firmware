#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h"
#include "channels.h"

#ifdef OLED_128x64
    #define SCREEN_WIDTH 128
    #define SCREEN_HEIGHT 64
#elif OLED_128x32
    #define SCREEN_WIDTH 128
    #define SCREEN_HEIGHT 32
#else
    #error Oled size not defined.
#endif

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

extern Adafruit_SSD1306 display;
extern String channelNames[NUM_OF_CHANNELS];

bool initOled();
void drawVolume(uint8_t volume, uint8_t channel);
void drawMute(uint8_t channel, bool unmute);
void clearOled();
void setOledBrightness(uint8_t brightness);