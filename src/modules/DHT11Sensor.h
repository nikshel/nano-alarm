#pragma once

#include <Arduino.h>
#include <DHT11.h>

class DHT11Sensor {
   private:
    DHT11 dht;
    uint8_t pin;
    int temperature = 0;
    int humidity = 0;

   public:
    DHT11Sensor(uint8_t pin);
    void init();
    void update();
    float getTemperature();
    float getHumidity();
};