#include "SleepManager.h"

bool SleepManager::wakeupByInterrupt = false;

SleepManager::SleepManager(uint8_t wakeupInterruptPin, unsigned long sleepDelay)
    : wakeupInterruptPin(wakeupInterruptPin), sleepDelay(sleepDelay) {
}

void SleepManager::init() {
    power.autoCalibrate();
    power.setSleepMode(POWERDOWN_SLEEP);
    power.setSleepResolution(SLEEP_1024MS);
    delaySleep();
    pinMode(wakeupInterruptPin, INPUT);
}

void SleepManager::delaySleep() {
    sleepAt = millis() + sleepDelay;
}

unsigned long SleepManager::sleep() {
    unsigned long start = millis();
    wakeupByInterrupt = false;
    attachInterrupt(digitalPinToInterrupt(wakeupInterruptPin), onWakeUp, RISING);
    while (!wakeupByInterrupt) {
        power.sleepDelay(80000);
    }
    detachInterrupt(digitalPinToInterrupt(wakeupInterruptPin));
    sleepAt = 0;
    return millis() - start;
}

void SleepManager::onWakeUp() {
    power.wakeUp();
    wakeupByInterrupt = true;
}

bool SleepManager::shouldSleep() const {
    return sleepEnabled && millis() >= sleepAt;
}

void SleepManager::enableSleep() {
    sleepEnabled = true;
    delaySleep();
}

void SleepManager::disableSleep() {
    sleepEnabled = false;
    sleepAt = 0;
}