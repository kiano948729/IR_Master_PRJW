#ifndef SLAVE_MANAGER_H
#define SLAVE_MANAGER_H

#include <stdint.h>

void SlaveManager_init();
void SlaveManager_update();
void SlaveManager_sendCommand(uint8_t slaveIndex, uint8_t command);
uint8_t SlaveManager_requestData(uint8_t slaveIndex);
bool SlaveManager_pingReceived(uint8_t slaveIndex);
void SlaveManager_resetPing(uint8_t slaveIndex);

#endif