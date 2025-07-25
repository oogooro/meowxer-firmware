#pragma once
#include "incomingPacket.h"

#define COMMAND_INCOMING_INIT 'i'
#define COMMAND_INCOMING_OLED 'o'
#define COMMAND_INCOMING_LEDS 'l'
#define COMMAND_INCOMING_FORCE_READ 'r'
#define COMMAND_INCOMING_CONFIG 'c'

#define COMMAND_OLED_ARGUMENT_SUBCOMMAND 0
#define COMMAND_OLED_ARGUMENT_VOLUME 1
#define COMMAND_OLED_ARGUMENT_BRIGHTNESS 1
#define COMMAND_OLED_ARGUMENT_MUTE_UNMUTE 1
#define COMMAND_OLED_ARGUMENT_MUTE_CHANNEL 2
#define COMMAND_OLED_SUBCOMMAND_VOLUME '0'
#define COMMAND_OLED_SUBCOMMAND_CLEAR '1'
#define COMMAND_OLED_SUBCOMMAND_BRIGHTNESS '2'
#define COMMAND_OLED_SUBCOMMAND_MUTE '3'

#define COMMAND_LEDS_ARGUMENT_SUBCOMMAND 0
#define COMMAND_LEDS_ARGUMENT_BRIGHTNESS 1
#define COMMAND_LEDS_SUBCOMMAND_SET '0'
#define COMMAND_LEDS_SUBCOMMAND_BRIGHTNESS '1'

extern void (*commandMap[128])(IncomingPacket* pkt);

void initHandler();
void handleInit(IncomingPacket* pkt);
void handleOled(IncomingPacket* pkt);
void handleLeds(IncomingPacket* pkt);
void handleForceRead(IncomingPacket* pkt);
void handleConfig(IncomingPacket* pkt);
