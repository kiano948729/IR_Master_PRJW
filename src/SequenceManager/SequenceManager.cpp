#include "SequenceManager.h"

static const uint8_t* correctSequence;
static uint8_t sequenceLength;
static uint8_t currentStep = 0;
static bool complete = false;

void SequenceManager_init(const uint8_t* sequence, uint8_t length)
{
    correctSequence = sequence;
    sequenceLength = length;
    currentStep = 0;
    complete = false;
}

bool SequenceManager_isCorrectStep(uint8_t address)
{
    if (complete) return false;
    if (address == correctSequence[currentStep])
    {
        currentStep++;
        if (currentStep >= sequenceLength) complete = true;
        return true;
    }
    currentStep = 0;
    return false;
}

void SequenceManager_recordActivation(uint8_t address)
{
    SequenceManager_isCorrectStep(address);
}

bool SequenceManager_isComplete()
{
    return complete;
}

void SequenceManager_reset()
{
    currentStep = 0;
    complete = false;
}

uint8_t SequenceManager_getCurrentStep()
{
    return currentStep;
}