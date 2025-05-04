#include "DHT11Sensor.h"

DHT11Sensor::DHT11Sensor(uint8_t pin) : dht(pin, DHT11) {
    this->pin = pin;
    this->temperature = 0;
    this->humidity = 0;
}

void DHT11Sensor::init() { dht.begin(); }

void DHT11Sensor::update() {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
}

float DHT11Sensor::getTemperature() { return temperature; }

float DHT11Sensor::getHumidity() { return humidity; }