/*
File:   DS1881-Example.ino
Author: J. Ian Lindsay
Date:   2019.10.20

DS1881 example.
*/

#include <Wire.h>
#include <DS1881.h>

#define TEST_PROG_VERSION "v1.0"


/*******************************************************************************
* Pin definitions and hardware constants.
*******************************************************************************/
#define SDA_PIN             18
#define SCL_PIN             19
#define LED0_PIN            13


/*******************************************************************************
* Globals
*******************************************************************************/
DS1881 dev(DS1881_BASE_I2C_ADDR);


/*******************************************************************************
* Functions to output things to the console
*******************************************************************************/

void printHelp() {
  Serial.print("\nDS1881E Example ");
  Serial.print(TEST_PROG_VERSION);
  Serial.print("\n---< Meta >-------------------------\n");
  Serial.print("?     This output\n");
  Serial.print("i     DS1881E info\n");

  Serial.print("\n---< Channel Manipulation >-----------\n");
  Serial.print("[/]   Volume up/down for channel 0\n");
  Serial.print("{/}   Volume up/down for channel 1\n");
  Serial.print("+/-   Volume up/down for both channels at once\n");
  Serial.print("x     Refresh register shadows\n");
  Serial.print("I     Reinitialize\n");
  Serial.print("#     Store wiper settings in NV\n");
  Serial.print("S     Serialize\n");
  Serial.print("R/r   Set range to 63/33\n");
  Serial.print("E/e   (En/Dis)able channel (mute)/\n");
  Serial.print("Z/z   (En/Dis)able zerocross detection\n");
}



/*******************************************************************************
* Setup function
*******************************************************************************/

void setup() {
  Serial.begin(115200);
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();
  dev.init();
}


/*******************************************************************************
* Main loop
*******************************************************************************/

void loop() {
  DIGITALPOT_ERROR ret = DIGITALPOT_ERROR::NO_ERROR;
  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case '[':
      case ']':
        ret = dev.setValue(0, dev.getValue(0) + (('[' == c) ? 1 : -1));
        Serial.print("setValue() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case '{':
      case '}':
        ret = dev.setValue(1, dev.getValue(1) + (('{' == c) ? 1 : -1));
        Serial.print("setValue() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case '-':
      case '+':
        ret = dev.setValue(dev.getValue(0) + (('-' == c) ? 1 : -1));
        Serial.print("setValue() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case 'Z':
      case 'z':
        ret = dev.zerocrossWait('Z' == c);
        Serial.print("zerocrossWait() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case 'E':
      case 'e':
        ret = dev.enable('E' == c);
        Serial.print("enable() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case '#':
        ret = dev.storeWipers();
        Serial.print("storeWipers() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case 'R':
      case 'r':
        ret = dev.setRange(('R' == c) ? 63 : 33);
        Serial.print("setRange() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case 'I':
        ret = dev.init();
        Serial.print("init() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case 'x':
        ret = dev.refresh();
        Serial.print("refresh() returns ");
        Serial.println(DS1881::errorToStr(ret));
        break;
      case 'S':   // Save the state into a buffer for later reconstitution.
        {
          uint8_t buffer[DS1881_SERIALIZE_SIZE];
          uint8_t written = dev.serialize(buffer, DS1881_SERIALIZE_SIZE);
          if (DS1881_SERIALIZE_SIZE == written) {
            for (uint8_t i = 0; i < DS1881_SERIALIZE_SIZE; i++) {
              Serial.print(buffer[i], HEX);
              Serial.print(" ");
            }
            Serial.println();
          }
          else {
            Serial.print("serialize() returns ");
            Serial.print(written);
            Serial.print(". Was expecting ");
            Serial.println(DS1881_SERIALIZE_SIZE);
          }
        }
        break;
      case 'i':  dev.printDebug();      break;
      case '?':  printHelp();           break;
    }
  }
}
