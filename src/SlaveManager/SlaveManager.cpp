#include <Arduino.h>
#include <Wire.h>
#include "SlaveManager.h"

#define MAX_SLAVES 8

static bool slaveOnline[MAX_SLAVES];

void SlaveManager_init() {
    Wire.begin();
    for (uint8_t i = 0; i < MAX_SLAVES; i++) {
        slaveOnline[i] = false;
    }
}

void SlaveManager_update() {
    for (uint8_t i = 0; i < MAX_SLAVES; i++) {
        uint8_t data = SlaveManager_requestData(i);
        if (data == 1 && !slaveOnline[i]) {
            slaveOnline[i] = true;
            Serial.print("Ping ontvangen van slave ");
            Serial.println(i);
        }
    }
}

void SlaveManager_sendCommand(uint8_t slaveIndex, uint8_t command) {
    if (slaveIndex >= MAX_SLAVES) return;
    uint8_t slaveAddress = slaveIndex + 1;
    Wire.beginTransmission(slaveAddress);
    Wire.write(command);
    Wire.endTransmission();
    Serial.print("I2C command gestuurd naar slave ");
    Serial.println(slaveIndex);
}

uint8_t SlaveManager_requestData(uint8_t slaveIndex) {
    if (slaveIndex >= MAX_SLAVES) return 0;
    uint8_t slaveAddress = slaveIndex + 1;
    Wire.requestFrom(slaveAddress, (uint8_t)1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0;
}

bool SlaveManager_pingReceived(uint8_t slaveIndex) {
    if (slaveIndex >= MAX_SLAVES) return false;
    return slaveOnline[slaveIndex];
}

void SlaveManager_resetPing(uint8_t slaveIndex) {
    if (slaveIndex >= MAX_SLAVES) return;
    slaveOnline[slaveIndex] = false;
}