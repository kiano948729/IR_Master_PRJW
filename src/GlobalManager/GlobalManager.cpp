#include <Arduino.h>
#include "GlobalManager.h"
#include "../SensorManager/SensorManager.h"
#include "../SlaveManager/SlaveManager.h"
#include "../SequenceManager/SequenceManager.h"

const uint8_t slaveAddresses[] = {1, 2};
#define SLAVE_COUNT (sizeof(slaveAddresses) / sizeof(slaveAddresses[0]))
const uint8_t correctSequence[] = {1, 2, 1, 1};
#define SEQUENCE_LENGTH (sizeof(correctSequence) / sizeof(correctSequence[0]))
const uint8_t sensorToSlaveAddress[] = {1, 2};

static bool puzzleSolved = false;

void GlobalManager_init()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("Master gestart");
    SensorManager_init();
    SlaveManager_init(slaveAddresses, SLAVE_COUNT);
    SensorManager_registerSensor(2);
    SensorManager_registerSensor(3);
    SequenceManager_init(correctSequence, SEQUENCE_LENGTH);
    Serial.println("Puzzel klaar");
}

void GlobalManager_update()
{
    if (puzzleSolved) return;
    SensorManager_update();
    SlaveManager_update();
    for (uint8_t i = 0; i < SLAVE_COUNT; i++)
    {
        if (SlaveManager_pingReceived(i))
        {
            uint8_t address = slaveAddresses[i];
            Serial.print("Slave ping activatie: ");
            Serial.println(address);
            SequenceManager_recordActivation(address);
            SlaveManager_resetPing(i);
            SlaveManager_sendCommand(i, 1);
            if (SequenceManager_isComplete())
            {
                Serial.println("PUZZEL OPGELOST!");
                puzzleSolved = true;
                for (uint8_t j = 0; j < SLAVE_COUNT; j++)
                    SlaveManager_sendCommand(j, 1);
            }
        }
    }
}