#include <Arduino.h>
#include "GlobalManager.h"
#include "../SensorManager/SensorManager.h"
#include "../SequenceManager/SequenceManager.h"
#include "../SlaveManager/SlaveManager.h"

const uint8_t slaveAddresses[] = {1, 2}; 
#define SLAVE_COUNT (sizeof(slaveAddresses)/sizeof(slaveAddresses[0]))

void GlobalManager_init() {
    Serial.begin(115200);
    delay(500);
    Serial.println("Master gestart");

    SensorManager_init();
    SequenceManager_init(SLAVE_COUNT);
    SlaveManager_init(slaveAddresses, SLAVE_COUNT);

    // register sensors
    SensorManager_registerSensor(2);
    SensorManager_registerSensor(3);
    SensorManager_registerSensor(4);
    SensorManager_registerSensor(5);
}

void GlobalManager_update() {
    SensorManager_update();
    SlaveManager_update();

    uint8_t lastSensor = SensorManager_getLastActivatedSensor();

    if (lastSensor != 255) {
        if (!SlaveManager_pingReceived(lastSensor)) {
            SlaveManager_sendCommand(lastSensor, 1);
        }
    }

    if (SequenceManager_isComplete()) {
        Serial.println("Sequence compleet -> reset");
        SequenceManager_resetSequence();
        SlaveManager_resetAllPings();
    }
}