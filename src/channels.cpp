#include "channels.h"
#include "packet.h"
#include "commands.h"

const uint8_t channelPins[NUM_OF_CHANNELS] = { PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7 };
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
            uint16_t sensor = readOversampled(channelPins[i]);

            if ((abs(pots[i] - sensor) >= uint8_t(SENSOR_THRESHOLD))) {
                pots[i] = sensor;
                potsMapped[i] = MAP(i);
                potsChanged = true;
            }
        }
        potsReadTimestamp = millis();
    }

    // if (potsChanged) {
    //     Packet potsDebug(COMMAND_OUTGOING_DEBUG);
    //     potsDebug.appendData("Channel raw values:");
    //     for (const auto value : pots) {
    //         potsDebug.appendData(value);
    //     }
    //     potsDebug.transmit();
    // }

    return potsChanged;
}

void forceUpdatePots() {
    for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
        uint16_t sensor = readOversampled(channelPins[i]);
        pots[i] = sensor;
        potsMapped[i] = MAP(i);
    }
}

uint16_t readOversampled(uint8_t pin) {
    uint32_t sum = 0;

    for (uint8_t i = 0; i < SENSOR_OVERSAMPLING; i++) {
        sum += analogRead(pin);
    }

    return sum / SENSOR_OVERSAMPLING;
}