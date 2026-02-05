#include <Arduino.h>
#include "SlaveManager.h"

#define MAX_SLAVES 8

static const uint8_t pingPins[MAX_SLAVES] = {8, 9, 10, 11, 12, 13, A0, A1};

static bool slaveOnline[MAX_SLAVES];

void SlaveManager_init() {
    for (uint8_t i = 0; i < MAX_SLAVES; i++) {
        pinMode(pingPins[i], INPUT);
        slaveOnline[i] = false;
    }
}

void SlaveManager_update() {
    for (uint8_t i = 0; i < MAX_SLAVES; i++) {
        if (digitalRead(pingPins[i]) == HIGH) {
            slaveOnline[i] = true;
            Serial.print("Ping ontvangen van slave ");
            Serial.println(i);
        }
    }
}

void SlaveManager_sendCommand(uint8_t slaveIndex) {
    // TODO: stuur signaal naar slave via output pin of I2C, afhankelijk van hardware
    Serial.print("Command gestuurd naar slave ");
    Serial.println(slaveIndex);
}

bool SlaveManager_pingReceived(uint8_t slaveIndex) {
    if (slaveIndex >= MAX_SLAVES) return false;
    return slaveOnline[slaveIndex];
}