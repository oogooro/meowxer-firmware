#include "oled.h"
#include "packet.h"
#include "commands.h"

Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
String channelNames[NUM_OF_CHANNELS];

bool initOled() {
    delay(100);
    bool s = display.begin(SCREEN_ADDRESS, true);

    display.clearDisplay();
    display.drawXBitmap(0, 16, BITMAP_logo2, SCREEN_WIDTH, 32, SH110X_WHITE);
    display.display();
    return s;
}

void drawVolume(uint8_t volume, uint8_t channel) {
    uint8_t x;
    uint16_t w;

    if (volume < 10) x = 40;
    else if (volume != 100) x = 30;
    else x = 16;

    w = (float(volume) / 100) * SCREEN_WIDTH;

    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(4);
    display.setCursor(x, 10);
    display.print(String(volume) + "%");
    display.drawFastHLine(0, SCREEN_HEIGHT - 1, w, SH110X_WHITE);
    display.setTextSize(2);
    display.setCursor(64 - (channelNames[channel].length() * 12 / 2), 46);
    display.print(channelNames[channel]);
    display.display();
}

void drawMute(uint8_t channel, bool unmute) {
    display.clearDisplay();
    display.drawXBitmap(30, 10, unmute ? BITMAP_sound : BITMAP_nosound, 32, 32, SH110X_WHITE);
    display.drawChar(74, 12, channel + '1', SH110X_WHITE, SH110X_BLACK, 4);
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(2);
    display.setCursor(64 - (channelNames[channel].length() * 12 / 2), 46);
    display.print(channelNames[channel]);
    display.display();
}

void clearOled() {
    display.clearDisplay();
    display.display();
}

void setOledBrightness(uint8_t brightness) {
    Packet dbg(COMMAND_OUTGOING_DEBUG);
    dbg.appendData("Oled brightness not implemented on this display");
    dbg.transmit();
    // display.ssd1306_command(SSD1306_SETCONTRAST);
    // display.ssd1306_command(brightness);
}