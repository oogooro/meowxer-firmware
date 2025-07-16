#pragma once
#include <Arduino.h>

class IncomingPacket {
    private:
    uint16_t separatorIndexes[64];
    const char* rawData;
    uint16_t dataSize = 0;
    public:
    uint8_t argCount = 1;
    char type;
    IncomingPacket(const char* rawBytes, uint16_t rawSize);
    String getArg(uint8_t index);
    int getArgInt(uint8_t index);
    char getArgChar(uint8_t index);
};