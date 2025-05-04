#include "LCDDisplay.h"

LCDDisplay::LCDDisplay() : lcd(LCD_ADDRESS, 16, 2) {}

void LCDDisplay::init() {
    lcd.init();
    turnOn();
}

void LCDDisplay::turnOn() { lcd.backlight(); }

void LCDDisplay::turnOff() { lcd.noBacklight(); }

void LCDDisplay::print(const char* text, uint8_t row) {
    lcd.setCursor(0, row);
    lcd.print(text);
}

void LCDDisplay::clear() { lcd.clear(); }