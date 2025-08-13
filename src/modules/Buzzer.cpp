#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin, bool silentMode) : _pin(pin), _isActive(false), _silentMode(silentMode) {}

void Buzzer::init() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

void Buzzer::start(unsigned int frequency) {
    if (!_isActive) {
        if (_silentMode) {
            Serial.println("BUZZER: ON (Silent Mode)");
        } else {
            tone(_pin, frequency);
        }
        _isActive = true;
    }
}

void Buzzer::stop() {
    if (_isActive) {
        if (_silentMode) {
            Serial.println("BUZZER: OFF (Silent Mode)");
        } else {
            noTone(_pin);
            digitalWrite(_pin, HIGH);
        }
        _isActive = false;
    }
}
