#include "SequenceManager.h"

static uint8_t activationSequence[MAX_SEQUENCE];
static uint8_t sequenceLength = 0;
static uint8_t expectedSequenceLength = 0;
static bool sequenceComplete = false;

void SequenceManager_init(uint8_t expectedLength)
{
    expectedSequenceLength = expectedLength;
    sequenceLength = 0;
    sequenceComplete = false;
}

void SequenceManager_recordActivation(uint8_t sensorIndex)
{
    if (sequenceComplete)
        return;

    if (sequenceLength < MAX_SEQUENCE)
    {
        activationSequence[sequenceLength] = sensorIndex;
        sequenceLength++;

        if (sequenceLength >= expectedSequenceLength)
        {
            sequenceComplete = true;
        }
    }
}

void SequenceManager_resetSequence()
{
    sequenceLength = 0;
    sequenceComplete = false;
}

uint8_t SequenceManager_getLength()
{
    return sequenceLength;
}

uint8_t SequenceManager_getStep(uint8_t index)
{
    if (index >= sequenceLength)
        return 255;
    return activationSequence[index];
}

bool SequenceManager_isComplete()
{
    return sequenceComplete;
}
