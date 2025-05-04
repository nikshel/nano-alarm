#include <Arduino.h>
#include <GyverOS.h>
#include <GyverPower.h>

#include "modules/Buzzer.h"
#include "modules/DHT11Sensor.h"
#include "modules/DistanceSensor.h"
#include "modules/LCDDisplay.h"
#include "modules/MoveSensor.h"
#include "modules/Radio.cpp"
#include "modules/SignalLed.h"
#include "modules/SleepManager.h"
#include "settings.h"

struct State {
    int distance;
    float temperature;
    float humidity;
    bool moveDetected = false;

    bool operator==(const State& other) const {
        return memcmp(this, &other, sizeof(State)) == 0;
    }
};

State state;
GyverOS<10> os;

LCDDisplay display;
DHT11Sensor dht(DHT_PIN);
DistanceSensor distanceSensor(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);
Buzzer buzzer(BUZZER_PIN, BUZZER_SILENT_MODE);
MoveSensor moveSensor(MOVE_SENSOR_PIN);
SignalLed signalLed(LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);
SleepManager sleepManager(MOVE_SENSOR_PIN, SLEEP_AFTER);
Radio radio(RADIO_CE_PIN, RADIO_CS_PIN);

void updateDistance() {
    distanceSensor.update();
    state.distance = distanceSensor.getDistance();
}

void updateTemperature() {
    dht.update();
    state.temperature = dht.getTemperature();
    state.humidity = dht.getHumidity();
}

State displayState;
void updateDisplay() {
    if (displayState == state) {
        return;
    }
    display.printf(0, "Dist: %d cm", state.distance);
    display.printf(1, "T:%.0fC H:%.0f%%", state.temperature, state.humidity);
    displayState = state;
}

void updateMoveSensor() {
    moveSensor.update();
    state.moveDetected = moveSensor.isMoveDetected();
}

void doBzz() {
    if (state.distance < DISTANCE_THRESHOLD || state.moveDetected) {
        buzzer.start();
        signalLed.turnOn(Colors::RED);
        sleepManager.delaySleep();
    } else {
        buzzer.stop();
        signalLed.turnOff();
    }
}

void sendRadioMessage() {
    int start = millis();
    bool sent = radio.sendMessage(Radio::State::OK, state.temperature, state.humidity);
    int end = millis();
    Serial.println("Sending radio message...");
    Serial.printf("Radio message sent: %d in %d ms\n", sent, end - start);
}

void setup() {
    Serial.begin(9600);
    Serial.println("Starting...");

    while (!radio.init()) {
        Serial.println("Failed to initialize radio");
        delay(1000);
    }
    sleepManager.init();
    display.init();
    dht.init();
    distanceSensor.init();
    buzzer.init();
    moveSensor.init();
    signalLed.init();

    os.attach(0, updateDistance, 100);
    os.attach(1, updateTemperature, 1000);
    os.attach(2, updateDisplay, 100);
    os.attach(3, updateMoveSensor, 100);
    // os.attach(4, doBzz, 100);
    os.attach(5, sendRadioMessage, 3000);
}

void loop() {
    os.tick();
    // if (sleepManager.shouldSleep()) {
    //     display.clear();
    //     display.printf(0, "Sleeping...");
    //     unsigned long slept = sleepManager.sleep();
    //     display.printf(0, "Awake after: %d ms", slept);
    //     sleepManager.delaySleep();
    // }
}
