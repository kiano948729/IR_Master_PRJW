#ifndef SEQUENCE_MANAGER_H
#define SEQUENCE_MANAGER_H

#include <stdint.h>

void SequenceManager_init(const uint8_t* sequence, uint8_t length);
void SequenceManager_recordActivation(uint8_t address);
bool SequenceManager_isComplete();
void SequenceManager_reset();
uint8_t SequenceManager_getCurrentStep();

#endif