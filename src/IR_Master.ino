#include <Arduino.h>
#include "GlobalManager/GlobalManager.h"

void setup()
{
    GlobalManager_init();
}

void loop()
{
    GlobalManager_update();
}