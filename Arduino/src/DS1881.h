/*
File:   DS1881.h
Author: J. Ian Lindsay
Date:   2019.07.13

Copyright 2016 Manuvr, Inc

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef __DS1881_DRIVER_H__
#define __DS1881_DRIVER_H__

#include <Arduino.h>


/* Hardware-defined registers */
#define DS1881_BASE_I2C_ADDR   0x28


enum class DIGITALPOT_ERROR : int8_t {
  DEVICE_DISABLED = 3,   // A caller tried to set a wiper while the device is disabled. This may work...
  PEGGED_MAX      = 2,   // There was no error, but a call to change a wiper setting pegged the wiper at its highest position.
  PEGGED_MIN      = 1,   // There was no error, but a call to change a wiper setting pegged the wiper at its lowest position.
  NO_ERROR        = 0,   // There was no error.
  ABSENT          = -1,  // The pot appears to not be connected to the bus.
  BUS             = -2,  // Something went wrong with the i2c bus.
  ALREADY_AT_MAX  = -3,  // A caller tried to increase the value of the wiper beyond its maximum.
  ALREADY_AT_MIN  = -4,  // A caller tried to decrease the value of the wiper below its minimum.
  INVALID_POT     = -5   // There aren't that many potentiometers.
};



class DS1881 {
  public:
    DS1881(uint8_t address);
    ~DS1881();

    void printDebug();

    inline uint8_t getValue(uint8_t pot) {
      return (pot > 1) ? 0 : 0x3F & registers[pot];
    };
    DIGITALPOT_ERROR init();                              // Perform bus-related init tasks.
    DIGITALPOT_ERROR setValue(uint8_t val);               // Sets the value of both pots.
    DIGITALPOT_ERROR setValue(uint8_t pot, uint8_t val);  // Sets the value of the given pot.
    DIGITALPOT_ERROR enable(bool);                        //
    DIGITALPOT_ERROR refresh();                           // Forces a shadow refresh from hardware.

    inline bool enabled() {   return _enabled; };

    DIGITALPOT_ERROR storeWipers();
    DIGITALPOT_ERROR zerocrossWait(bool enable);
    inline bool zerocrossWait() {  return (registers[2] & 0x02);  };

    /* Returns the maximum value of any single potentiometer. */
    inline uint16_t getRange() {  return ((registers[2] & 0x01) ? 33 : 63);  };
    DIGITALPOT_ERROR setRange(uint8_t);

    static const char* const errorToStr(DIGITALPOT_ERROR);


  private:
    const   uint8_t _ADDR;
    bool    dev_init = false;
    bool    _enabled = false;
    uint8_t registers[3]  = {0, 0, 0};
    uint8_t alt_values[2] = {0, 0};

    int8_t _read_registers();
    int8_t _write_register(uint8_t reg, uint8_t val);
};

#endif   // __DS1881_DRIVER_H__
