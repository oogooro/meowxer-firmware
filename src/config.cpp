#include "config.h"
#include "packet.h"
#include "commands.h"

uint32_t configBitfieldPersistant = 0;
uint32_t configBitfieldCommon = 0;

void setConfigBitfield(const uint8_t field, const uint32_t bitfield) {
    switch (field) {
        case CONFIG_BITFIELD_PERSISTANT:
        configBitfieldPersistant = bitfield;
        writePersistantBitfield();
        break;
        case CONFIG_BITFIELD_COMMON:
        configBitfieldCommon = bitfield;
        break;
        default:
            Packet dbg(COMMAND_OUTGOING_DEBUG);
            dbg.appendData("Config bitfield not found.");
            dbg.transmit();
    }
}

// TODO: implement
uint32_t readPersistantBitfield(void) {
    return 0;
}

// TODO: implement
bool writePersistantBitfield(void) {
    return false;
}
