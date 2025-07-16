#include "channels.h"

const uint8_t channelPins[NUM_OF_CHANNELS] = { PA0, PA1, PA2, PA3, PA4 };
uint16_t pots[NUM_OF_CHANNELS] = {};
uint8_t potsMapped[NUM_OF_CHANNELS] = {};
unsigned long potsReadTimestamp = millis();

void channelSetup() {
    analogReadResolution(12);
    for (const auto channelPin : channelPins) {
        pinMode(channelPin, INPUT);
    }
}

bool readPots() {
    bool potsChanged = false;
    if (millis() - potsReadTimestamp >= 1000 / SENSOR_POOLINGRATE) {
        for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
            uint16_t sensor = analogRead(channelPins[i]);
            if ((abs(pots[i] - sensor) >= uint8_t(SENSOR_THRESHOLD))) {
                pots[i] = sensor;
                potsMapped[i] = MAP(i);
                potsChanged = true;
            }
        }
        potsReadTimestamp = millis();
    }
    return potsChanged;
}

void forceUpdatePots() {
    for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
        uint16_t sensor = analogRead(channelPins[i]);
        pots[i] = sensor;
        potsMapped[i] = MAP(i);
    }
}