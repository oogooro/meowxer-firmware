#include "commands.h"
#include "oled.h"
#include "leds.h"
#include "channels.h"
#include "packet.h"
#include "config.h"
#include "main.h"

void (*commandMap[128])(IncomingPacket* pkt) { nullptr };

void initHandler() {
    commandMap[COMMAND_INCOMING_INIT] = handleInit;
    commandMap[COMMAND_INCOMING_OLED] = handleOled;
    commandMap[COMMAND_INCOMING_LEDS] = handleLeds;
    commandMap[COMMAND_INCOMING_FORCE_READ] = handleForceRead;
    commandMap[COMMAND_INCOMING_CONFIG] = handleConfig;
}

void handleInit(IncomingPacket* pkt) {
    initalized = true;
}

void handleOled(IncomingPacket* pkt) {
    const char subcommand = pkt->getArgChar(COMMAND_OLED_ARGUMENT_SUBCOMMAND);

    if (subcommand == COMMAND_OLED_SUBCOMMAND_VOLUME) {
        drawVolume(pkt->getArgInt(COMMAND_OLED_ARGUMENT_VOLUME), pkt->getArgInt(COMMAND_OLED_ARGUMENT_VOLUME_CHANNEL));
    } else if (subcommand == COMMAND_OLED_SUBCOMMAND_CLEAR) {
        clearOled();
    } else if (subcommand == COMMAND_OLED_SUBCOMMAND_BRIGHTNESS) {
        setOledBrightness(pkt->getArgInt(COMMAND_OLED_ARGUMENT_BRIGHTNESS));
    } else if (subcommand == COMMAND_OLED_SUBCOMMAND_MUTE) {
        drawMute(pkt->getArgInt(COMMAND_OLED_ARGUMENT_MUTE_CHANNEL), pkt->getArgChar(COMMAND_OLED_ARGUMENT_MUTE_UNMUTE) == '1');
    } else if (subcommand == COMMAND_OLED_SUBCOMMAND_REGISTER_CHANNEL_NAMES) {
        for (uint8_t i = COMMAND_OLED_ARGUMENT_REGISTER_CHANNEL_NAMES_START; i < pkt->argCount; i++) {
            if (i > NUM_OF_CHANNELS) break;
            channelNames[i - COMMAND_OLED_ARGUMENT_REGISTER_CHANNEL_NAMES_START] = pkt->getArgDecoded(i);
        }
    }
}

void handleLeds(IncomingPacket* pkt) {
    const char subcommand = pkt->getArgChar(COMMAND_LEDS_ARGUMENT_SUBCOMMAND);

    if (subcommand == COMMAND_LEDS_SUBCOMMAND_SET) {
        uint8_t numberOfLeds = min(NUM_OF_LEDS, pkt->argCount - 1); 
        bool states[numberOfLeds];

        for (uint8_t i = 0; i < numberOfLeds; i++) {
            states[i] = pkt->getArgChar(i + 1) == '1';
        }

        ledSet(states);
    } else if (subcommand == COMMAND_LEDS_SUBCOMMAND_BRIGHTNESS) {
        ledSetBrightness(pkt->getArgInt(COMMAND_LEDS_ARGUMENT_BRIGHTNESS));
    }
}

void handleForceRead(IncomingPacket* pkt) {
    forceUpdatePots();
    Packet potsPacket('=');
    for (auto pot : potsMapped) {
        potsPacket.appendData(pot);
    }
    potsPacket.transmit();
}

void handleConfig(IncomingPacket* pkt) {
}
