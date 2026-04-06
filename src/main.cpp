#include <Arduino.h>
#include "main.h"
#include "config.h"
#include "packet.h"
#include "incomingPacket.h"
#include "oled.h"
#include "channels.h"
#include "leds.h"
#include "buttons.h"
#include "commands.h"
#include "heartbeat.h"

bool initalized = false;

void sendBootPacket() {
  Packet bootPacket(COMMAND_OUTGOING_BOOT);
  bootPacket.appendData(SERIAL_PROTO_VERSION);
  bootPacket.appendData(HARDWARE_VERSION);
  bootPacket.appendData(NUM_OF_CHANNELS);
  bootPacket.transmit();
}

void setup() {
  Serial.begin();
  Wire.begin();
  
  initHandler();
  channelSetup();
  buttonsSetup();
  ledSetup();

  initOled();
  
  ledAnim();
  delay(100);
  
  display.clearDisplay();
  display.display();

  while (!Serial) {};
  delay(200);
  sendBootPacket();
}

void loop() {
  if (!Serial) { // Driver disconnected
    onDisconnect();
    while (!Serial) {} // Wait for serial
    delay(200);
    sendBootPacket();
  }

  if (Serial.available()) {
    char buffer[512];
    uint16_t capturedBytes = Serial.readBytesUntil('\n', buffer, 512);

    IncomingPacket incoming(buffer, capturedBytes);

    char type = incoming.type;
    auto command = commandMap[(size_t)type];

    if (command != nullptr) {
      command(&incoming);
    }
  }

  if (initalized) {
    if (readPots()) {
      Packet potsPacket(COMMAND_OUTGOING_CHANNELS);
      for (auto pot : potsMapped) {
        potsPacket.appendData(pot);
      }
      potsPacket.transmit();
    }

    if (readButtons()) {
      Packet buttonsPacket(COMMAND_OUTGOING_BUTTONS);
      buttonsPacket.appendData(pressedButtons);
      buttonsPacket.transmit();
    }

    if (configBitfieldCommon & CONFIG_BITFIELD_COMMON_HEARTBEAT_ENABLED) {
      heartbeat();
    }
  }
}

void onDisconnect(void) {
  initalized = false;
  clearOled();
  bool ledsAllOff[NUM_OF_LEDS]{ false };
  ledSet(ledsAllOff);
  configBitfieldCommon = 0;
}
