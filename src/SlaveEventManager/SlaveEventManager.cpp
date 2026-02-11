#include "SlaveEventManager.h"
#include <Wire.h>

static const int sensorPin = A0;
static const int outPin = 7;
static volatile uint8_t command = 0;
static volatile uint8_t status = 0;
static uint8_t slaveAddress = 0;
static int baseline = 0;
static bool calibrated = false;
static bool lastState = false;
static bool pingSent = false;

void receiveEvent(int bytes)
{
    if (Wire.available())
        command = Wire.read();
}

void requestEvent()
{
    Wire.write(status);
}

void SlaveEventManager_init(uint8_t address)
{
    slaveAddress = address;
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

static unsigned long lastPingTime = 0;
#define PING_COOLDOWN 1000  

void SlaveEventManager_update()
{
    int value = analogRead(sensorPin);
    if (!calibrated)
    {
        baseline = value + 50;
        calibrated = true;
    }
    bool currentState = (value > baseline);

    unsigned long now = millis();

    if (command == 1)
    {
        if (currentState && !lastState && (now - lastPingTime > PING_COOLDOWN))
        {
            status = 1;
            pingSent = true;
            lastPingTime = now;
            tone(outPin, 2000, 100);
        }
        else
        {
            status = 0;
        }
    }
    else
    {
        status = 0;
        pingSent = false;
    }

    if (!currentState) {
        pingSent = false;
    }

    lastState = currentState;
}