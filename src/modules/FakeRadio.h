#pragma once

#include "IRadio.h"

class FakeRadio : public IRadio {
   public:
    FakeRadio(int cePin, int csPin);
    bool init() override;
    bool sendMessage(State state, float temperature, float humidity) override;

   private:
    int cePin;
    int csPin;
};
