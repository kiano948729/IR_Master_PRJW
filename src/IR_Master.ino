#include <Arduino.h>
#include "GlobalManager/GlobalManager.h"

#define SLAVE_ADDRESS 1
void setup()
{
    GlobalManager_init();
}

void loop()
{
    GlobalManager_update();
}