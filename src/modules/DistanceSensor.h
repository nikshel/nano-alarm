#pragma once

#include <Arduino.h>

class DistanceSensor {
   public:
    DistanceSensor(uint8_t triggerPin, uint8_t echoPin);
    void init();
    void update();
    int getDistance() const;

   private:
    uint8_t _triggerPin;
    uint8_t _echoPin;
    int _distance;
};