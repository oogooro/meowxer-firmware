#include "heartbeat.h"
#include "config.h"
#include "packet.h"
#include "commands.h"

ulong lastHeartbeatSendTimestamp;
uint8_t hearbeatCounter = 0;
uint8_t heartbeatAckFailedTimes = 0;

bool heartbeat() {
    if (millis() - lastHeartbeatSendTimestamp >= HEARTBEAT_INTERVAL) {
        Packet pkt(COMMAND_OUTGOING_HEARTBEAT);
        pkt.appendData(COMMAND_HEARTBEAT_PING);
        pkt.appendData(hearbeatCounter++);
        pkt.transmit();
        lastHeartbeatSendTimestamp = millis();
        return true;
    }
    
    return false;
}
