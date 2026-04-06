#pragma once
#include <Arduino.h>

#define SERIAL_PROTO_VERSION 2
#define HARDWARE_VERSION 3

#define CONFIG_BITFIELD_PERSISTANT 0

#define CONFIG_BITFIELD_COMMON 1
#define CONFIG_BITFIELD_COMMON_HEARTBEAT_ENABLED (1 << 0)

extern uint32_t configBitfieldPersistant;
extern uint32_t configBitfieldCommon;

void setConfigBitfield(const uint8_t field, const uint32_t bitfield);
uint32_t readPersistantBitfield(void);
bool writePersistantBitfield(void);