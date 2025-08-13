#include "PasswordManager.h"

#include "EncButton.h"
#include "LCDDisplay.h"

void PasswordManager::askForPassword() {
    reset();
    display.clear();
    display.print(F("Enter password"));
    printCurrentInput(display);
}

bool PasswordManager::onEncoderAction(EncButton &encoder) {
    if (completed) {
        return true;
    }

    switch (encoder.getAction()) {
        case EBAction::Turn:
            if (encoder.right()) {
                if (input[index] == 9) {
                    input[index] = 0;
                } else {
                    input[index]++;
                }
            } else {
                if (input[index] == 0) {
                    input[index] = 9;
                } else {
                    input[index]--;
                }
            }
            break;
        case EBAction::Clicks:
            if (encoder.clicks == 1) {
                if (index == 3) {
                    completed = true;
                    return true;
                } else {
                    index++;
                }
            } else if (index != 0) {
                index--;
            }
            break;
        default:
            break;
    }
    printCurrentInput(display);
    return false;
}

bool PasswordManager::isPasswordCorrect() {
    for (int i = 0; i < 4; i++) {
        if (input[i] != correct[i]) {
            return false;
        }
    }
    return true;
}

void PasswordManager::reset() {
    input[0] = 0;
    input[1] = 0;
    input[2] = 0;
    input[3] = 0;
    index = 0;
    completed = false;
}

void PasswordManager::printCurrentInput(LCDDisplay &display) {
    char buf[4 + 4 + 2];
    int pos = 0;
    for (int i = 0; i < 4; i++) {
        if (i == index) {
            buf[pos] = '[';
            buf[pos + 1] = '0' + input[i];
            buf[pos + 2] = ']';
            pos += 3;
        } else {
            buf[pos] = '0' + input[i];
            pos++;
        }
        buf[pos] = ' ';
        pos++;
    }
    buf[pos] = '\0';
    display.print(buf, 1);
}
