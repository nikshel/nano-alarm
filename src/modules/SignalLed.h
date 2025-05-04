#pragma once

#include <Arduino.h>

enum class Colors { RED, GREEN, BLUE };

class SignalLed {
   public:
    SignalLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
    void init();
    void turnOn(Colors color);
    void turnOff();

   private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _bluePin;
};