#include "FakeRadio.h"

FakeRadio::FakeRadio(int cePin, int csPin) : cePin(cePin), csPin(csPin) {
}

bool FakeRadio::init() {
    Serial.printf(F("FakeRadio::init(CE=%d, CS=%d)\n"), cePin, csPin);
    return true;
}

bool FakeRadio::sendMessage(State state, float temperature, float humidity) {
    Serial.print(F("FakeRadio::sendMessage - State: "));
    Serial.print(state == State::OK ? F("OK") : F("ALARM"));
    Serial.print(F(", Temperature: "));
    Serial.print(temperature);
    Serial.print(F("C, Humidity: "));
    Serial.print(humidity);
    Serial.println(F("%"));
    return true;
}
