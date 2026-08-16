#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "bitmaps.h"
#include "channels.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define OLED_RESET     -1
#ifndef SCREEN_ADDRESS
    #define SCREEN_ADDRESS 0x3C
#endif

extern Adafruit_SH1107 display;
extern String channelNames[NUM_OF_CHANNELS];

bool initOled();
void drawVolume(uint8_t volume, uint8_t channel);
void drawMute(uint8_t channel, bool unmute);
void clearOled();
void setOledBrightness(uint8_t brightness);