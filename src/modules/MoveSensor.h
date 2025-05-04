#pragma once

#include <Arduino.h>

class MoveSensor {
   public:
    MoveSensor(uint8_t pin);
    void init();
    void update();
    bool isMoveDetected() const;

   private:
    uint8_t _pin;
    bool _moveDetected;
};