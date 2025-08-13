#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class LCDDisplay {
   private:
    LiquidCrystal_I2C lcd;

   public:
    static const uint8_t LCD_ADDRESS = 0x27;
    static const uint8_t LCD_WIDTH = 16;

    LCDDisplay();

    void init();
    void turnOn();
    void turnOff();
    // void print(const char* text, uint8_t row = 0);
    // void print(const String& text, uint8_t row = 0);

    template <typename T>
    void print(const T& text, uint8_t row = 0) {
        lcd.setCursor(0, row);
        lcd.print(text);
    }

    void clear();

    template <typename... Args>
    void printf(uint8_t row, const __FlashStringHelper* format, Args... args) {
        lcd.setCursor(0, row);
        lcd.printf(format, args...);

        for (uint8_t i = 0; i < LCD_WIDTH; i++) {
            lcd.write(' ');
        }
    }
};
