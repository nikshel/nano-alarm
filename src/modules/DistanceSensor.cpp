#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(uint8_t triggerPin, uint8_t echoPin) : _triggerPin(triggerPin), _echoPin(echoPin), _distance(0) {}

void DistanceSensor::init() {
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

void DistanceSensor::update() {
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    _distance = pulseIn(_echoPin, HIGH) / 58.2;
}

int DistanceSensor::getDistance() const { return _distance; }