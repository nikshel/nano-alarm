#pragma once

#include <Arduino.h>
#include <GyverPower.h>

class SleepManager {
   public:
    SleepManager(uint8_t wakeupInterruptPin, unsigned long sleepDelay);

    void init();
    void delaySleep();
    unsigned long sleep();
    bool shouldSleep() const;
    void enableSleep();
    void disableSleep();

   private:
    static void onWakeUp();

    uint8_t wakeupInterruptPin;
    unsigned long sleepDelay;
    unsigned long sleepAt = 0;
    static bool wakeupByInterrupt;
    bool sleepEnabled = true;
};