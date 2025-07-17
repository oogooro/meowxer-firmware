#include <Arduino.h>
#include "main.h"
#include "config.h"
#include "packet.h"
#include "incomingPacket.h"
#include "oled128x32.h"
#include "channels.h"
#include "leds.h"
#include "buttons.h"
#include "commands.h"

bool initalized = false;

void sendBootPacket() {
  Packet bootPacket('$');
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

  delay(100); // oled takes additional 25ms to turn on
  initOled();
  
  display.drawXBitmap(0, 0, BITMAP_logo2, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
  
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
    initalized = false;
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
      Packet potsPacket('=');
      for (auto pot : potsMapped) {
        potsPacket.appendData(pot);
      }
      potsPacket.transmit();
    }

    if (readButtons()) {
      Packet buttonsPacket('b');
      buttonsPacket.appendData(pressedButtons);
      buttonsPacket.transmit();
    }
  }
}
