#pragma once

#include <Arduino.h>
#include <DHT.h>

class DHT11Sensor {
   private:
    DHT dht;
    uint8_t pin;
    float temperature;
    float humidity;

   public:
    DHT11Sensor(uint8_t pin);
    void init();
    void update();
    float getTemperature();
    float getHumidity();
};