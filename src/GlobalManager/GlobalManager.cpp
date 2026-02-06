#include <Arduino.h>
#include "GlobalManager.h"
#include "../SensorManager/SensorManager.h"
#include "../SequenceManager/SequenceManager.h"
#include "../SlaveManager/SlaveManager.h"

#define SLAVE_COUNT 4

void GlobalManager_init()
{
    Serial.begin(115200);
    Serial.println("Master gestart");
    SensorManager_init();
    SequenceManager_init(SLAVE_COUNT);
    SlaveManager_init(SLAVE_COUNT);

    SensorManager_registerSensor(2);
    SensorManager_registerSensor(3);
    SensorManager_registerSensor(4);
    SensorManager_registerSensor(5);
}

void GlobalManager_update()
{
    SensorManager_update();
    SlaveManager_update();

    uint8_t lastSensor = SensorManager_getLastActivatedSensor();

    if (lastSensor != 255)
    {
        Serial.print("Sensor geactiveerd: ");
        Serial.println(lastSensor);

        if (!SlaveManager_pingReceived(lastSensor))
        {
            Serial.print("Command gestuurd naar slave ");
            Serial.println(lastSensor);
            SlaveManager_sendCommand(lastSensor, 1);
        }
    }

    if (SequenceManager_isComplete())
    {
        Serial.println("Sequence compleet → reset");
        SequenceManager_resetSequence();
        SlaveManager_resetAllPings();
    }
}
