#pragma once

#include <bitset>
#include "esphome.h"

void updateUnknownSelect(uint16_t sensorIndex, esphome::modbus_controller::ModbusSelect *selectComp);
void setTime(esphome::modbus_controller::ModbusController *controller);
