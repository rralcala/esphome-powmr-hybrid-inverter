#include <bitset>
#include <string>
#include <iostream>
#include "esphome.h"
#include "esphome/core/log.h"
#include "myHelpers.h"

void updateUnknownSelect(uint16_t sensorIndex, esphome::modbus_controller::ModbusSelect* selectComp)
{
  const char* logTag = "myHelpers";
  if (!selectComp->active_index().has_value() || sensorIndex != selectComp->active_index().value()) {
    //esphome::ESP_LOGW(logTag, "Update select to index %d", sensorIndex);
    auto call = selectComp->make_call();
    call.set_index(sensorIndex);
    call.perform();
  }
}



