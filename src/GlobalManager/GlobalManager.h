#ifndef GLOBAL_MANAGER_H
#define GLOBAL_MANAGER_H

#include <stdint.h>

void GlobalManager_init();
void GlobalManager_update();

uint8_t SequenceManager_getCurrentLength();
const uint8_t* SequenceManager_getCurrentSequence();
#endif