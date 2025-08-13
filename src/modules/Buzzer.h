#pragma once

#include <Arduino.h>

class Buzzer {
   public:
    Buzzer(uint8_t pin, bool silentMode = false);
    void init();
    void start(unsigned int frequency);
    void stop();

   private:
    uint8_t _pin;
    bool _isActive;
    bool _silentMode;
};