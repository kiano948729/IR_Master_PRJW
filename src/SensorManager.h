#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <stdint.h>

#define MAX_SENSORS 8

void SensorManager_init();
void SensorManager_registerSensor(uint8_t pin);
void SensorManager_update();

uint8_t SensorManager_getSensorCount();
unsigned long SensorManager_getSensorActivationCount(uint8_t sensorIndex);
uint8_t SensorManager_getLastActivatedSensor();
unsigned long SensorManager_getTotalActivations();

#endif