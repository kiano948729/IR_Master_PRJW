#include <Arduino.h>
#include "GlobalManager.h"
#include "../SensorManager/SensorManager.h"
#include "../SequenceManager/SequenceManager.h"
#include "../SlaveManager/SlaveManager.h"

void GlobalManager_init() {
    SensorManager_init();
    SlaveManager_init();

    SensorManager_registerSensor(2); // pin connectie naar slave
    SensorManager_registerSensor(3); // pin connectie naar slave
    SensorManager_registerSensor(4); // pin connectie naar slave
    SensorManager_registerSensor(5); // pin connectie naar slave
}

void GlobalManager_update() {
    SensorManager_update();
    SlaveManager_update();

    uint8_t lastSensor = SensorManager_getLastActivatedSensor();
    if (lastSensor != 255 && !SlaveManager_pingReceived(lastSensor)) {
        SlaveManager_sendCommand(lastSensor, 1);
    }

    if (SequenceManager_isComplete()) {
        SequenceManager_resetSequence();
        for (uint8_t i = 0; i < SensorManager_getSensorCount(); i++) {
            SlaveManager_resetPing(i);
        }
    }
}