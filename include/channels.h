#pragma once
#include <Arduino.h>
#include <config.h>

#define SENSOR_POOLINGRATE 140
#define SENSOR_THRESHOLD 38
#define SENSOR_MAX_VALUE 4095
#define SENSOR_MAX_OVERHEAD 50
#define NUM_OF_CHANNELS 8
#define SENSOR_OVERSAMPLING 6
#define MAP(x) (min(map(pots[x], 0, SENSOR_MAX_VALUE - SENSOR_MAX_OVERHEAD, 0, 100), 100L))

extern uint8_t potsMapped[NUM_OF_CHANNELS];

void channelSetup();
bool readPots();
void forceUpdatePots();
uint16_t readOversampled(uint8_t pin);