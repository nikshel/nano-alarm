#include "DHT11Sensor.h"

DHT11Sensor::DHT11Sensor(uint8_t pin) : dht(pin) {
    this->pin = pin;
    dht.setDelay(0);
}

void DHT11Sensor::init() {}

void DHT11Sensor::update() {
    dht.readTemperatureHumidity(temperature, humidity);
}

float DHT11Sensor::getTemperature() { return temperature; }

float DHT11Sensor::getHumidity() { return humidity; }