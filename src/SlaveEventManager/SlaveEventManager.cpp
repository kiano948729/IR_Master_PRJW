#include "SlaveEventManager.h"
#include <Wire.h>

const int altPin = A0;
int baseval = 0;
const int outpin = 7;
const int ledPin = 7;

bool ran = false;
int status = 0;

void SlaveEventManager_init() {
    Wire.begin(1);
    Wire.onRequest(SlaveEventManager_sendData);
    pinMode(altPin, INPUT);
    pinMode(outpin, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

void SlaveEventManager_update() {
    if (!ran) {
        int baseVal = analogRead(altPin);
        if (baseVal != 0) {
            baseval = (baseVal * 10);
            ran = true;
        }
    } else {
        int altStat = analogRead(altPin);
        if (altStat >= baseval) {
            tone(outpin, 2000);
            digitalWrite(ledPin, HIGH);
            delay(200);
            noTone(outpin);
            digitalWrite(ledPin, LOW);
            status = 1;
        } else {
            digitalWrite(ledPin, LOW);
            status = 0;
        }
    }
}

void SlaveEventManager_sendData() {
    Wire.write(status);
}