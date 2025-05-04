#include "MoveSensor.h"

MoveSensor::MoveSensor(uint8_t pin) : _pin(pin), _moveDetected(false) {
}

void MoveSensor::init() {
    pinMode(_pin, INPUT);
}

void MoveSensor::update() {
    _moveDetected = digitalRead(_pin) == HIGH;
}

bool MoveSensor::isMoveDetected() const {
    return _moveDetected;
}