#include <Arduino.h>
#include <EncButton.h>
#include <Looper.h>

#include "modules/Buzzer.h"
#include "modules/DHT11Sensor.h"
// #include "modules/DistanceSensor.h"
#include "modules/LCDDisplay.h"
// #include "modules/MoveSensor.h"
#include "modules/PasswordManager.h"
#include "modules/Radio.cpp"
// #include "modules/SignalLed.h"
#include "modules/SleepManager.h"
#include "settings.h"

namespace NAlarm {

enum Status {
    STANDBY,
    ALARM_WAITING_FOR_PASSWORD,
    ALARMING
};

enum Event {
    START,
    MOVE_DETECTED,
    PASSWORD_CORRECT,
    PASSWORD_TIMEOUT,
};

struct State {
    Status status;
    int distance;
    float temperature;
    float humidity;

    bool operator==(const State& other) const {
        return memcmp(this, &other, sizeof(State)) == 0;
    }
};

volatile State state;
void processEvent(Event event);

LCDDisplay display;
DHT11Sensor dht(DHT_PIN);
// DistanceSensor distanceSensor(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);
Buzzer buzzer(BUZZER_PIN, BUZZER_SILENT_MODE);
// MoveSensor moveSensor(MOVE_SENSOR_PIN);
// SignalLed signalLed(LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);
SleepManager sleepManager(MOVE_SENSOR_PIN, SLEEP_AFTER);
Radio radio(RADIO_CE_PIN, RADIO_CS_PIN);
PasswordManager passwordManager(display);

EncButton encoder(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_BTN_PIN);

// bool hasDisplayState = false;
// State displayState;
// void updateDisplay() {
//     if (hasDisplayState && displayState == state) {
//         return;
//     }
//     display.printf(0, F("Dist: %d cm"), state.distance);
//     display.printf(1, F("T:%.0fC H:%.0f%%"), state.temperature, state.humidity);
//     displayState = state;
//     hasDisplayState = true;
// }

// void updateMoveSensor() {
//     moveSensor.update();
//     state.moveDetected = moveSensor.isMoveDetected();
// }

void sendRadioMessage() {
    Radio::State radioState = state.status == Status::ALARMING ? Radio::State::ALARM : Radio::State::OK;
    Serial.println(F("Sending radio message..."));
    int start = millis();
    bool sent = radio.sendMessage(radioState, state.temperature, state.humidity);
    int end = millis();
    Serial.printf(F("Radio message sent status %s\n"), sent ? F("success") : F("fail"));
    Serial.printf(F("Spent time: %d ms\n"), end - start);
}

enum BuzzerCommand {
    GOOD_BEEP,
    BAD_BEEP
};
const char* BUZZER_LISTENER_ID = "buzzer";
void onBuzzerCommand() {
    BuzzerCommand* cmd = (BuzzerCommand*)Looper.eventData();
    Serial.printf(F("Buzzer command: %s\n"), *cmd == GOOD_BEEP ? F("GOOD_BEEP") : *cmd == BAD_BEEP ? F("BAD_BEEP")
                                                                                                   : F("UNKNOWN"));
    auto frequency = *cmd == GOOD_BEEP ? 1000 : 500;
    buzzer.start(frequency);

    new LoopTimer(1000, []() {
        buzzer.stop();
        delete Looper.thisTask();
    });
    delete cmd;
}

void tickEncoder() {
    if (encoder.tick()) {
        bool inputCompleted = passwordManager.onEncoderAction(encoder);
        if (inputCompleted) {
            if (passwordManager.isPasswordCorrect()) {
                processEvent(Event::PASSWORD_CORRECT);
            } else {
                passwordManager.askForPassword();
            }
        }
    }
}

void updateTemperature() {
    dht.update();
    state.temperature = dht.getTemperature();
    state.humidity = dht.getHumidity();
}

static LoopListener buzzerListener(BUZZER_LISTENER_ID, onBuzzerCommand);
static LoopTicker encoderTicker(tickEncoder);
static LoopTimer updateTemperatureTimer(1000, updateTemperature);
static LoopTimer radioStatusTimer(60UL * 1000, sendRadioMessage);

void processEvent(Event event) {
    switch (event) {
        case START:
            state.status = Status::STANDBY;
            encoderTicker.disable();
            display.turnOff();
            radioStatusTimer.force();
            break;
        case MOVE_DETECTED:
            if (state.status == Status::STANDBY) {
                state.status = Status::ALARM_WAITING_FOR_PASSWORD;
                encoderTicker.enable();
                display.turnOn();
                sleepManager.disableSleep();
                passwordManager.askForPassword();
            }
            break;
        case PASSWORD_CORRECT:
            state.status = Status::STANDBY;
            encoderTicker.disable();
            display.turnOff();
            sendRadioMessage();
            sleepManager.enableSleep();
            Looper.pushEvent(BUZZER_LISTENER_ID, new BuzzerCommand(GOOD_BEEP));
            break;
        case PASSWORD_TIMEOUT:
            state.status = Status::ALARMING;
            sendRadioMessage();
            break;
    }
}

void setup() {
    while (!radio.init()) {
        Serial.println("Failed to initialize radio");
        delay(1000);
    }
    sleepManager.init();
    encoder.setClickTimeout(200);
    display.init();
    dht.init();
    // distanceSensor.init();
    buzzer.init();
    // moveSensor.init();

    processEvent(START);
}

}  // namespace NAlarm

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting..."));
    NAlarm::setup();
}

void loop() {
    Looper.loop();
}
