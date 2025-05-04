#include <SPI.h>

#include "RF24.h"
#include "nRF24L01.h"

class Radio {
   public:
    enum State : uint8_t {
        OK = 0,
        ALARM = 1,
    };
    struct Message {
        constexpr static char magicBytes[2] = {'N', 'K'};
        constexpr static uint8_t version = 1;
        State state;
        float temperature;
        float humidity;
    };

    Radio(int cePin, int csPin) : radio(cePin, csPin) {
    }

    bool init() {
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

    bool sendMessage(State state, float temperature, float humidity) {
        Message message;
        message.state = state;
        message.temperature = temperature;
        message.humidity = humidity;

        radio.powerUp();
        bool success = radio.write(&message, sizeof(Message));
        radio.powerDown();
        return success;
    }

   private:
    static constexpr uint8_t ADDRESS[5] = {'A', 'L', 'A', 'R', 'M'};
    RF24 radio;
};