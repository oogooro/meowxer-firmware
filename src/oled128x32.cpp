#include "oled128x32.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool initOled() {
    return display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

void drawVolume(uint8_t volume) {
    uint8_t x;
    uint16_t w;

    if (volume < 10) x = 40;
    else if (volume != 100) x = 32;
    else x = 24;

    w = (float(volume) / 100) * SCREEN_WIDTH;

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(3);
    display.setCursor(x, 5);
    display.print(String(volume) + "%");
    display.drawFastHLine(0, SCREEN_HEIGHT - 1, w, SSD1306_WHITE);
    display.display();
}

void drawMute(uint8_t channel, bool unmute) {
    display.clearDisplay();
    display.drawXBitmap(23, 0, unmute ? BITMAP_sound : BITMAP_nosound, 32, 32, SSD1306_WHITE);
    display.drawChar(65, 5, channel + '1', SSD1306_WHITE, SSD1306_BLACK, 3);
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