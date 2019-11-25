/*
File:   DS1881.cpp
Author: J. Ian Lindsay
Date:   2016.12.26

Copyright 2019 Manuvr, Inc

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


This class always enabled zero-cross. This induces a latency to wiper change.
Class also configures the device for maximum resolution.
*/

#include "DS1881.h"
#include <Wire.h>

#define DS1881_REG_WR0   0x00
#define DS1881_REG_WR1   0x40
#define DS1881_REG_CONF  0x80



/*******************************************************************************
*   ___ _              ___      _ _              _      _
*  / __| |__ _ ______ | _ ) ___(_) |___ _ _ _ __| |__ _| |_ ___
* | (__| / _` (_-<_-< | _ \/ _ \ | / -_) '_| '_ \ / _` |  _/ -_)
*  \___|_\__,_/__/__/ |___/\___/_|_\___|_| | .__/_\__,_|\__\___|
*                                          |_|
* Constructors/destructors, class initialization functions and so-forth...
*******************************************************************************/

DS1881::DS1881(uint8_t addr) : _ADDR(addr) {
  dev_init    = false;
}


DS1881::~DS1881() {
}


/*
* Dump this item to the dev log.
*/
void DS1881::printDebug() {
  Serial.print("DS1881 digital potentiometer");

  if (!dev_init) {
    Serial.println("\tNot initialized\n");
    return;
  }

  for (int i = 0; i < 2; i++) {
    Serial.print("\n\tPOT ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(0x3F & registers[i], DEC);
  }
  Serial.print("\n\tCONF:  0x");
  Serial.print((int8_t) registers[2], HEX);
  Serial.print("\n\talt_values[0]:  ");
  Serial.print((int8_t) alt_values[0], DEC);
  Serial.print("\n\talt_values[1]:  ");
  Serial.print((int8_t) alt_values[1], DEC);
  Serial.print("\n\tRange:          ");
  Serial.print(getRange(), DEC);
  Serial.print("\n\tZero-cross:     ");
  Serial.println((zerocrossWait()) ? "Enabled":"Disabled");
}



/*******************************************************************************
* Class-specific functions...                                                  *
*******************************************************************************/
/*
* Call to read the device and cause this class's state to reflect that of the device.
*/
DIGITALPOT_ERROR DS1881::init() {
  DIGITALPOT_ERROR return_value = DIGITALPOT_ERROR::BUS;
  if (0 == _read_registers()) {
    return_value = DIGITALPOT_ERROR::NO_ERROR;
  }
  Serial.print("init() returns ");
  Serial.println((int8_t) return_value, DEC);
  return return_value;
}


/*
* Set the value of the given wiper to the given value.
*/
DIGITALPOT_ERROR DS1881::setValue(uint8_t pot, uint8_t val) {
  if (pot > 1)    return DIGITALPOT_ERROR::INVALID_POT;
  if (!dev_init)  return DIGITALPOT_ERROR::DEVICE_DISABLED;

  DIGITALPOT_ERROR return_value = DIGITALPOT_ERROR::NO_ERROR;
  uint8_t range = (uint8_t) getRange();
  uint8_t tmp_val = min(val, range);
  if (range == tmp_val) {
    return_value = (tmp_val == val) ? DIGITALPOT_ERROR::PEGGED_MAX : DIGITALPOT_ERROR::ALREADY_AT_MAX;
  }
  else if (0 == tmp_val) {
    return_value = DIGITALPOT_ERROR::PEGGED_MIN;
  }

  if (0 <= (int8_t) return_value) {
    registers[pot] = (pot << 6) | tmp_val;
    if (0 == _write_register(pot << 6, registers[pot])) {
      return_value = DIGITALPOT_ERROR::NO_ERROR;
    }
  }
  Serial.print("setValue(pot) returns ");
  Serial.println((int8_t) return_value, DEC);
  return return_value;
}


/*
* Set the value of the given wiper to the given value.
*/
DIGITALPOT_ERROR DS1881::setValue(uint8_t val) {
  DIGITALPOT_ERROR return_value = setValue(0, val);
  if (DIGITALPOT_ERROR::NO_ERROR == return_value) {
    return_value = setValue(1, val);
  }
  return return_value;
}


/*
* Enabling the device unmutes it by restoring the previous value from the alt_values array.
* Disabling the device stacks the current value into alt_values and then sets to mute.
* Retains wiper settings.
*/
DIGITALPOT_ERROR DS1881::enable(bool x) {
  DIGITALPOT_ERROR return_value = DIGITALPOT_ERROR::NO_ERROR;
  if (x ^ _enabled) {
    if (x) {
      _write_register(DS1881_REG_WR0, alt_values[0]);
      _write_register(DS1881_REG_WR1, alt_values[1]);
    }
    else {
      uint8_t range = (uint8_t) getRange();
      alt_values[0] = registers[0];
      alt_values[1] = registers[1];
      _write_register(DS1881_REG_WR0, range);
      _write_register(DS1881_REG_WR1, range);
    }
    _enabled = x;
  }
  return return_value;
}


/*
* Make this state non-volatile.
*/
DIGITALPOT_ERROR DS1881::storeWipers() {
  DIGITALPOT_ERROR return_value = DIGITALPOT_ERROR::BUS;
  // Temporarily change the wiper volatility bit to write to the NVM...
  if (0 == _write_register(DS1881_REG_CONF, (registers[2] & 0x07) & ~0x04)) {
    // Store the wiper(s).
    if (0 == _write_register(DS1881_REG_WR0, registers[0])) {
      if (0 == _write_register(DS1881_REG_WR1, registers[1])) {
        // Set the wipers back to volatile.
        //if (0 == _write_register(DS1881_REG_CONF, (registers[2] & 0x07) | 0x04)) {
          return_value = DIGITALPOT_ERROR::NO_ERROR;
        //}
      }
    }
  }

  return return_value;
}


DIGITALPOT_ERROR DS1881::zerocrossWait(bool en) {
  int8_t return_value = _write_register(DS1881_REG_CONF, (en ? (registers[2] | 0x02) : (registers[2] & ~0x02)));
  return (0 == return_value) ? DIGITALPOT_ERROR::NO_ERROR : DIGITALPOT_ERROR::BUS;
}


DIGITALPOT_ERROR DS1881::setRange(uint8_t val) {
  int8_t return_value = -1;
  switch (val) {
    case 33:
    case 63:
      return_value = _write_register(DS1881_REG_CONF, ((33 == val) ? (registers[2] | 0x01) : (registers[2] & ~0x01)));
    default:
      break;
  }
  return (0 == return_value) ? DIGITALPOT_ERROR::NO_ERROR : DIGITALPOT_ERROR::BUS;
}



int8_t DS1881::_write_register(uint8_t reg, uint8_t val) {
  int8_t ret = -1;
  if (reg == (reg & 0xC0)) {
    Wire.beginTransmission(_ADDR);
    Wire.write((0x3F & val) | reg);
    if (0 == Wire.endTransmission()) {
      registers[reg >> 6] = val;
      ret = 0;
    }
  }
  return ret;
}


int8_t DS1881::_read_registers() {
  int8_t ret = -1;
  if (3 == Wire.requestFrom(_ADDR, (uint8_t) 3)) {
    ret = 0;
    registers[0] = 0x3F & Wire.receive();
    registers[1] = 0x3F & Wire.receive();
    registers[2] = 0x3F & Wire.receive();
  }

  if (0x04 != (registers[2] & 0x04)) {
    // Enforces volatile wiper operation unless specified otherwise.
    ret = _write_register(DS1881_REG_CONF, (registers[2] & 0x07) | 0x04);
  }
  dev_init = (0 == ret);
  return ret;
}
