#pragma once
#include <Arduino.h>

#define HEARTBEAT_INTERVAL 2000

extern ulong lastHeartbeatSendTimestamp;
extern uint8_t hearbeatCounter;
extern uint8_t heartbeatAckFailedTimes;

// return true on heartbeat send
bool heartbeat(void);