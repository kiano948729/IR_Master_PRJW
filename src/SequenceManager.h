#ifndef SEQUENCE_MANAGER_H
#define SEQUENCE_MANAGER_H

#include <stdint.h>

#define MAX_SEQUENCE 32

void SequenceManager_recordActivation(uint8_t sensorIndex);
void SequenceManager_resetSequence();

uint8_t SequenceManager_getLength();
uint8_t SequenceManager_getStep(uint8_t index);

bool SequenceManager_isComplete();

#endif