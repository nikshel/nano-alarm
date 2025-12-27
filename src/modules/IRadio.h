#pragma once

#include <Arduino.h>

class IRadio {
   public:
    enum State : uint8_t {
        OK = 0,
        ALARM = 1,
    };

    virtual ~IRadio() = default;
    virtual bool init() = 0;
    virtual bool sendMessage(State state, float temperature, float humidity) = 0;
};
