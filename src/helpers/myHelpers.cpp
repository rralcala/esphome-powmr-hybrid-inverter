#include <bitset>
#include <iostream>
#include <string>
#include "esphome.h"
#include "esphome/core/log.h"
#include "myHelpers.h"

void updateUnknownSelect(uint16_t sensorIndex, esphome::modbus_controller::ModbusSelect *selectComp)
{
  const char *logTag = "myHelpers";
  if (!selectComp->active_index().has_value() || sensorIndex != selectComp->active_index().value())
  {
    // esphome::ESP_LOGW(logTag, "Update select to index %d", sensorIndex);
    auto call = selectComp->make_call();
    call.set_index(sensorIndex);
    call.perform();
  }
}

void setTime(esphome::modbus_controller::ModbusController *controller)
{
  time_t now = ::time(nullptr);
  struct tm *time_info = ::localtime(&now);
  int seconds = time_info->tm_sec;
  int minutes = time_info->tm_min;
  int hour = time_info->tm_hour;
  int day = time_info->tm_mday;
  int dow = time_info->tm_wday;
  int month = time_info->tm_mon + 1;
  int year = time_info->tm_year;
  year = year - 100;
  // if there is no internet connection localtime returns year 70
  if (year != 70)
  {
    // create the payload
    std::vector<uint16_t> rtc_data = {uint16_t(year << 8 & month), uint16_t(day << 8 & hour), uint16_t(minutes << 8 & seconds)};
    // Create a modbus command item with the time information as the payload
    esphome::modbus_controller::ModbusCommandItem set_rtc_command =
        esphome::modbus_controller::ModbusCommandItem::create_write_multiple_command(controller, 0x20C, rtc_data.size(), rtc_data);
    // Submit the command to the send queue
    controller->queue_command(set_rtc_command);
    ESP_LOGI("SetTime", "SRNE RTC set to %02d:%02d:%02d %02d.%02d.%02d", hour, minutes, seconds, day, month,
             year);
  }
}
