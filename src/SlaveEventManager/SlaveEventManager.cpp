#include "SlaveEventManager.h"
#include <Wire.h>

static const int sensorPin = A0;
static const int outPin = 7;

static volatile uint8_t command = 0;
static volatile uint8_t status = 0;

static int baseline = 0;
static bool calibrated = false;

static unsigned long lastBeep = 0;

void receiveEvent(int bytes)
{
    if (Wire.available())
    {
        command = Wire.read();
    }
}

void requestEvent()
{
    Wire.write(status);
}

void SlaveEventManager_init(uint8_t address)
{
    Serial.begin(115200);
    delay(500);
    Serial.print("Slave gestart op adres ");
    Serial.println(address);

    Wire.begin(address);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    pinMode(sensorPin, INPUT);
    pinMode(outPin, OUTPUT);
}

void SlaveEventManager_update()
{
    int value = analogRead(sensorPin);

    if (!calibrated)
    {
        baseline = value + 50;
        calibrated = true;

        Serial.print("Baseline ingesteld op ");
        Serial.println(baseline);
    }

    if (command == 1)
    {
        if (value > baseline)
        {
            if (status == 0)
            {
                Serial.print("Beep! Sensorwaarde: ");
                Serial.println(value);
            }

            status = 1;

            if (millis() - lastBeep > 200)
            {
                tone(outPin, 2000, 100);
                lastBeep = millis();
            }
        }
        else
        {
            status = 0;
        }
    }
    else
    {
        status = 0;
    }
}
