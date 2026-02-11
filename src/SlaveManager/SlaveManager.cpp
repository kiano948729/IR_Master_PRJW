#include <Arduino.h>
#include <Wire.h>
#include "SlaveManager.h"

#define MAX_SLAVES 8

static bool slaveOnline[MAX_SLAVES];
static uint8_t slaveCount = 0;
static const uint8_t* slaveAddresses = nullptr;

void SlaveManager_init(const uint8_t* addresses, uint8_t count) {
    Wire.begin();
    slaveCount = count;
    slaveAddresses = addresses;

    for (uint8_t i = 0; i < slaveCount; i++) {
        slaveOnline[i] = false;
    }
}

void SlaveManager_update() {
    for (uint8_t i = 0; i < slaveCount; i++) {
        uint8_t address = slaveAddresses[i];

        Wire.requestFrom(address, (uint8_t)1);

        unsigned long start = millis();
        while (!Wire.available() && (millis() - start < 50)) {
        }

        if (Wire.available()) {
            uint8_t data = Wire.read();
            if (data > 0 && !slaveOnline[i]) {
                slaveOnline[i] = true;
                Serial.print("Ping ontvangen van slave ");
                Serial.println(address);
            }
        }

        delay(10); 
    }
}

void SlaveManager_sendCommand(uint8_t slaveIndex, uint8_t command) {
    if (slaveIndex >= slaveCount) return;
    uint8_t address = slaveAddresses[slaveIndex];

    Wire.beginTransmission(address);
    Wire.write(command);
    Wire.endTransmission();
}

bool SlaveManager_pingReceived(uint8_t slaveIndex) {
    if (slaveIndex >= slaveCount) return false;
    return slaveOnline[slaveIndex];
}

void SlaveManager_resetPing(uint8_t slaveIndex) {
    if (slaveIndex >= slaveCount) return;
    slaveOnline[slaveIndex] = false;
}

void SlaveManager_resetAllPings() {
    for (uint8_t i = 0; i < slaveCount; i++) {
        slaveOnline[i] = false;
    }
}