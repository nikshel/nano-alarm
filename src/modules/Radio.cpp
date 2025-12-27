#include "Radio.h"

#include <SPI.h>

#include "nRF24L01.h"

Radio::Radio(int cePin, int csPin) : radio(cePin, csPin) {
}

bool Radio::init() {
    bool success = radio.begin();
    if (!success) {
        return false;
    }
    radio.setChannel(120);
    radio.setRetries(10, 1);
    radio.setPayloadSize(sizeof(Message));
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.setCRCLength(RF24_CRC_16);
    radio.openWritingPipe(ADDRESS);
    radio.stopListening();
    return true;
}

bool Radio::sendMessage(State state, float temperature, float humidity) {
    Message message;
    message.state = state;
    message.temperature = temperature;
    message.humidity = humidity;

    radio.powerUp();
    bool success = radio.write(&message, sizeof(Message));
    radio.powerDown();
    return success;
}
