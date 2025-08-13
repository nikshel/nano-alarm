#pragma once

#include "EncButton.h"
#include "LCDDisplay.h"

class PasswordManager {
   public:
    PasswordManager(LCDDisplay &display) : display(display) {}

    void askForPassword();
    bool onEncoderAction(EncButton &encoder);
    bool isPasswordCorrect();

   private:
    void reset();
    void printCurrentInput(LCDDisplay &display);

    LCDDisplay &display;
    uint8_t correct[4] = {1, 0, 0, 0};
    uint8_t input[4];
    uint8_t index;
    bool completed;
};
