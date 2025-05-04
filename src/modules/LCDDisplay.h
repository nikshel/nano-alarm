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
    void print(const char* text, uint8_t row = 0);
    void clear();

    template <typename... Args>
    void printf(uint8_t row, const char* format, Args... args) {
        char buffer[LCD_WIDTH + 1];
        snprintf(buffer, LCD_WIDTH + 1, format, args...);
        lcd.setCursor(0, row);
        lcd.print(buffer);

        // Заполняем оставшиеся символы пробелами
        for (uint8_t i = strlen(buffer); i < LCD_WIDTH; i++) {
            lcd.write(' ');
        }
    }
};
