#include <Arduino.h>
#include "GlobalManager.h"
#include "../SensorManager/SensorManager.h"
#include "../SlaveManager/SlaveManager.h"
#include "../SequenceManager/SequenceManager.h"
#include <Wire.h>

const uint8_t slaveAddresses[] = {1, 2};
#define SLAVE_COUNT (sizeof(slaveAddresses) / sizeof(slaveAddresses[0]))

const uint8_t correctSequence[] = {1, 2, 1};
#define SEQUENCE_LENGTH (sizeof(correctSequence) / sizeof(correctSequence[0]))

const uint8_t sensorToSlaveAddress[] = {1, 2};

#define LCD_SLAVE_ADDR 0x10

void sendSequenceToLCD()
{
    char buffer[17];
    uint8_t length = SequenceManager_getCurrentLength();
    const uint8_t *seq = SequenceManager_getCurrentSequence();

    buffer[0] = 'S';
    buffer[1] = ':';

    for (uint8_t i = 0; i < length && i < 14; i++)
    {
        buffer[2 + i] = seq[i] + '0';
    }

    buffer[2 + length] = '\0';

    Wire.beginTransmission(LCD_SLAVE_ADDR);
    Wire.write(buffer);
    Wire.endTransmission();

    Serial.print("LCD sequence gestuurd: ");
    Serial.println(buffer);
}

void sendCodeToLCD(const char *code)
{
    char buffer[17];

    buffer[0] = 'C';
    buffer[1] = ':';

    uint8_t i = 0;
    while (code[i] != '\0' && i < 14)
    {
        buffer[2 + i] = code[i];
        i++;
    }

    buffer[2 + i] = '\0';

    Wire.beginTransmission(LCD_SLAVE_ADDR);
    Wire.write(buffer);
    Wire.endTransmission();

    Serial.print("LCD code gestuurd: ");
    Serial.println(buffer);
}

static bool puzzleSolved = false;
static unsigned long puzzleStartTime = 0;
static const unsigned long PUZZLE_TIMEOUT = 60000; // 60 seconden

void startPuzzleTimer()
{
    puzzleStartTime = millis();
}

void resetPuzzle()
{
    puzzleSolved = false;
    SequenceManager_reset();
    SlaveManager_resetAllPings();
    startPuzzleTimer();
    sendSequenceToLCD();
    Serial.println("Puzzel is gereset!");
}

void GlobalManager_init()
{
    Serial.begin(115200);
    delay(500);

    Wire.begin();

    Serial.println("Master gestart");

    SensorManager_init();
    SlaveManager_init(slaveAddresses, SLAVE_COUNT);

    SensorManager_registerSensor(2);
    SensorManager_registerSensor(3);

    SequenceManager_init(correctSequence, SEQUENCE_LENGTH);

    Serial.println("Puzzel klaar");

    startPuzzleTimer(); // start timer bij begin
}

void GlobalManager_update()
{
    SensorManager_update();
    SlaveManager_update();

    unsigned long now = millis();

    if (now - puzzleStartTime > PUZZLE_TIMEOUT)
    {
        resetPuzzle();
        return;
    }

    if (puzzleSolved)
        return;

    for (uint8_t i = 0; i < SLAVE_COUNT; i++)
    {
        if (SlaveManager_pingReceived(i))
        {
            uint8_t address = slaveAddresses[i];

            Serial.print("Slave ping activatie: ");
            Serial.println(address);

            SequenceManager_recordActivation(address);
            sendSequenceToLCD();
            SlaveManager_resetPing(i);
            SlaveManager_sendCommand(i, 1);

            if (SequenceManager_isComplete())
            {
                Serial.println("PUZZEL OPGELOST!");
                puzzleSolved = true;

                sendCodeToLCD("428");

                for (uint8_t j = 0; j < SLAVE_COUNT; j++)
                {
                    SlaveManager_sendCommand(j, 1);
                }

                startPuzzleTimer(); // start 60 seconden timer na oplossen
            }
        }
    }
}