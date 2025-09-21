#ifdef OLED_128x64
#include "oled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
String channelNames[NUM_OF_CHANNELS];

bool initOled() {
    delay(100);
    bool s = display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

    display.clearDisplay();
    display.drawXBitmap(0, 16, BITMAP_logo2, SCREEN_WIDTH, 32, SSD1306_WHITE);
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
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(4);
    display.setCursor(x, 10);
    display.print(String(volume) + "%");
    display.drawFastHLine(0, SCREEN_HEIGHT - 1, w, SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(64 - (channelNames[channel].length() * 12 / 2), 46);
    display.print(channelNames[channel]);
    display.display();
}

void drawMute(uint8_t channel, bool unmute) {
    display.clearDisplay();
    display.drawXBitmap(30, 10, unmute ? BITMAP_sound : BITMAP_nosound, 32, 32, SSD1306_WHITE);
    display.drawChar(74, 12, channel + '1', SSD1306_WHITE, SSD1306_BLACK, 4);
    display.setTextColor(SSD1306_WHITE);
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
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(brightness);
}
#endif