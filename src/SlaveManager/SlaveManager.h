#ifndef SLAVE_MANAGER_H
#define SLAVE_MANAGER_H

#include <stdint.h>

void SlaveManager_init(const uint8_t* addresses, uint8_t count);
void SlaveManager_update();
void SlaveManager_sendCommand(uint8_t slaveIndex, uint8_t command);
bool SlaveManager_pingReceived(uint8_t slaveIndex);
void SlaveManager_resetPing(uint8_t slaveIndex);
void SlaveManager_resetAllPings();

#endif