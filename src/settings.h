#pragma once

// Пины
const uint8_t DHT_PIN = 4;
const uint8_t ULTRASONIC_TRIGGER_PIN = 8;
const uint8_t ULTRASONIC_ECHO_PIN = 7;
const uint8_t BUZZER_PIN = 4;
const uint8_t MOVE_SENSOR_PIN = 2;
const uint8_t LED_RED_PIN = 3;
const uint8_t LED_GREEN_PIN = 5;
const uint8_t LED_BLUE_PIN = 6;
const uint8_t RADIO_CE_PIN = 10;
const uint8_t RADIO_CS_PIN = 9;

// Прерывание для пробуждения
const uint8_t WAKEUP_INTERRUPT = digitalPinToInterrupt(MOVE_SENSOR_PIN);
static_assert(WAKEUP_INTERRUPT != NOT_AN_INTERRUPT, "WAKEUP_INTERRUPT is not an interrupt");

// Настройки работы
const bool BUZZER_SILENT_MODE = true;
const int SLEEP_AFTER = 4096;
const int DISTANCE_THRESHOLD = 20;
