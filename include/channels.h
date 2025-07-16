#pragma once
#include <Arduino.h>
#include <config.h>

#define SENSOR_POOLINGRATE 30
#define SENSOR_THRESHOLD 38
#define SENSOR_MAX_VALUE 4095
#define SENSOR_MAX_OVERHEAD 50
#define NUM_OF_CHANNELS 5
#define MAP(x) (min(map(pots[x], 0, SENSOR_MAX_VALUE - SENSOR_MAX_OVERHEAD, 0, 100), 100L))

extern uint8_t potsMapped[NUM_OF_CHANNELS];

void channelSetup();
bool readPots();
void forceUpdatePots();