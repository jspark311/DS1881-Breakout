#include <Wire.h>
#include <DS1881.h>

DS1881 dev(DS1881_BASE_I2C_ADDR);


void setup() {
  Serial.begin(115200);
  Wire.setSDA(18);
  Wire.setSCL(19);
  Wire.begin();
  dev.init();
}


void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case '[':
      case ']':
        dev.setValue(0, dev.getValue(0) + (('[' == c) ? -1 : 1));
        break;
      case '{':
      case '}':
        dev.setValue(1, dev.getValue(1) + (('{' == c) ? -1 : 1));
        break;
      case '-':
      case '+':
        dev.setValue(dev.getValue(0) + (('-' == c) ? -1 : 1));
        break;
      case 'Z':
      case 'z':
        if (DIGITALPOT_ERROR::NO_ERROR == dev.zerocrossWait('Z' == c)) {
          Serial.println("Zerocross setting changed.");
        }
        break;
      case 'R':
      case 'r':
        if (DIGITALPOT_ERROR::NO_ERROR == dev.setRange(('R' == c) ? 63 : 33)) {
          Serial.println("Range changed.");
        }
        break;
      case 'M':
      case 'm':
        if (DIGITALPOT_ERROR::NO_ERROR == dev.enable('M' == c)) {
          Serial.println("Mute state changed.");
        }
        break;
      case 'S':
        if (DIGITALPOT_ERROR::NO_ERROR == dev.storeWipers()) {
          Serial.println("State saved to NVM.");
        }
        break;
      case 'x':
        if (DIGITALPOT_ERROR::NO_ERROR == dev.init()) {
          Serial.println("Device initialized.");
        }
        break;
      case 'i':
        dev.printDebug();
        break;
    }
  }
}
