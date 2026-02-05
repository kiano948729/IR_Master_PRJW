#include "Arduino.h"
#include "GlobalManager.h"
#include "SensorManager/SensorManager.h"
#include "SequenceManager/SequenceManager.h"

void GlobalManager_init()
{
    SensorManager_init();

    SensorManager_registerSensor(2); // pin connectie naar slave
    SensorManager_registerSensor(3); // pin connectie naar slave
    SensorManager_registerSensor(4); // pin connectie naar slave
    SensorManager_registerSensor(5); // pin connectie naar slave
}

void GlobalManager_update()
{
    SensorManager_update();
}