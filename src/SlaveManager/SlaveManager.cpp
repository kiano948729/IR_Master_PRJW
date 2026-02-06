#include <Arduino.h>
#include <Wire.h>
#include "SlaveManager.h"

#define MAX_SLAVES 8

static bool slaveOnline[MAX_SLAVES];
static uint8_t slaveCount = 0;

void SlaveManager_init(uint8_t count)
{
Wire.begin();
slaveCount = count;

for (uint8_t i = 0; i < slaveCount; i++)
{
    slaveOnline[i] = false;
}

}

void SlaveManager_update()
{
    for (uint8_t i = 0; i < slaveCount; i++)
    {
        uint8_t data = SlaveManager_requestData(i);

        if (data == 1 && !slaveOnline[i])
        {
            slaveOnline[i] = true;
            Serial.print("Ping ontvangen van slave ");
            Serial.println(i);
        }
    }
}

void SlaveManager_sendCommand(uint8_t slaveIndex, uint8_t command)
{
if (slaveIndex >= slaveCount) return;

uint8_t address = slaveIndex + 1;

Wire.beginTransmission(address);
Wire.write(command);
Wire.endTransmission();

}

uint8_t SlaveManager_requestData(uint8_t slaveIndex)
{
if (slaveIndex >= slaveCount) return 0;

uint8_t address = slaveIndex + 1;

Wire.requestFrom(address, (uint8_t)1);

if (Wire.available())
{
    return Wire.read();
}

return 0;

}

bool SlaveManager_pingReceived(uint8_t slaveIndex)
{
if (slaveIndex >= slaveCount) return false;

return slaveOnline[slaveIndex];

}

void SlaveManager_resetPing(uint8_t slaveIndex)
{
if (slaveIndex >= slaveCount) return;

slaveOnline[slaveIndex] = false;

}

void SlaveManager_resetAllPings()
{
for (uint8_t i = 0; i < slaveCount; i++)
{
slaveOnline[i] = false;
}
}
