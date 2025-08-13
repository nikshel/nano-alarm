#include "LCDDisplay.h"

LCDDisplay::LCDDisplay() : lcd(LCD_ADDRESS, 16, 2) {}

void LCDDisplay::init() {
    lcd.init();
}

void LCDDisplay::turnOn() { lcd.backlight(); }

void LCDDisplay::turnOff() { lcd.noBacklight(); }

void LCDDisplay::clear() { lcd.clear(); }
