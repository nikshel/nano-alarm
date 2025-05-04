#include "SignalLed.h"

SignalLed::SignalLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
    : _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin) {}

void SignalLed::init() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
    turnOff();
}

void SignalLed::turnOn(Colors color) {
    turnOff();
    switch (color) {
        case Colors::RED:
            analogWrite(_redPin, 255);
            break;
        case Colors::GREEN:
            analogWrite(_greenPin, 255);
            break;
        case Colors::BLUE:
            analogWrite(_bluePin, 255);
            break;
    }
}

void SignalLed::turnOff() {
    analogWrite(_redPin, 0);
    analogWrite(_greenPin, 0);
    analogWrite(_bluePin, 0);
}