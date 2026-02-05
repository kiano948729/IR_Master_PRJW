#ifndef SLAVE_MANAGER_H
#define SLAVE_MANAGER_H

#include <stdint.h>

void SlaveManager_init();
void SlaveManager_update();

// Slave acties
void SlaveManager_sendCommand(uint8_t slaveIndex);
bool SlaveManager_pingReceived(uint8_t slaveIndex);

#endif