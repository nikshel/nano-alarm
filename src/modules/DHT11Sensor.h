#pragma once

#include <Arduino.h>
// #include <DHT11.h>
#include "DHT.h"

class DHT11Sensor {
   private:
    DHT dht;
    uint8_t pin;
    float temperature = 0;
    float humidity = 0;

   public:
    DHT11Sensor(uint8_t pin);
    void init();
    void update();
    float getTemperature();
    float getHumidity();
};
