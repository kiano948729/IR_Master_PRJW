#include <Arduino.h>
#include "SensorManager.h"
#include "../SequenceManager/SequenceManager.h"

struct Sensor
{
uint8_t pin;
bool currentState;
bool lastState;
unsigned long activationCount;
};

static Sensor sensors[MAX_SENSORS];
static uint8_t sensorCount = 0;
static uint8_t lastActivatedSensor = 255;
static unsigned long totalActivations = 0;

void SensorManager_init()
{
sensorCount = 0;
lastActivatedSensor = 255;
totalActivations = 0;
}

void SensorManager_registerSensor(uint8_t pin)
{
if (sensorCount >= MAX_SENSORS) return;

sensors[sensorCount].pin = pin;
sensors[sensorCount].currentState = false;
sensors[sensorCount].lastState = false;
sensors[sensorCount].activationCount = 0;

pinMode(pin, INPUT);

sensorCount++;

}

static void recordActivation(uint8_t index)
{
sensors[index].activationCount++;
totalActivations++;
lastActivatedSensor = index;
SequenceManager_recordActivation(index);
}

void SensorManager_update()
{
for (uint8_t i = 0; i < sensorCount; i++)
{
bool state = digitalRead(sensors[i].pin);

    if (state && !sensors[i].lastState)
    {
        recordActivation(i);
    }

    sensors[i].lastState = state;
    sensors[i].currentState = state;
}

}

uint8_t SensorManager_getSensorCount()
{
return sensorCount;
}

unsigned long SensorManager_getSensorActivationCount(uint8_t index)
{
if (index >= sensorCount) return 0;
return sensors[index].activationCount;
}

uint8_t SensorManager_getLastActivatedSensor()
{
return lastActivatedSensor;
}

unsigned long SensorManager_getTotalActivations()
{
return totalActivations;
}
