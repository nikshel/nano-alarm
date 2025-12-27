#pragma once

#include "IRadio.h"
#include "RF24.h"

class Radio : public IRadio {
   public:
    Radio(int cePin, int csPin);
    bool init() override;
    bool sendMessage(State state, float temperature, float humidity) override;

   private:
    struct Message {
        constexpr static char magicBytes[2] = {'N', 'K'};
        constexpr static uint8_t version = 1;
        State state;
        float temperature;
        float humidity;
    };

    static constexpr uint8_t ADDRESS[5] = {'A', 'L', 'A', 'R', 'M'};
    RF24 radio;
};
