#include <Wire.h>
#include <Adafruit_MCP23017.h>

#include <Joystick.h>
#include "MyEncoder.h"

//https://github.com/MHeironimus/ArduinoJoystickLibrary
Joystick_ Joystick(0x04, 0x05, 12, 0, false, false, false, false, false, false, false, false, false, false, false);
//https://www.nikolaus-lueneburg.de/2015/11/mcp23017-i2c-io-port-expander/
Adafruit_MCP23017 mcp1;

void encoderChange(int8_t change, int8_t decreaseButton, int8_t increaseButton) {
  if (change == -1) {
    Serial.println("decreased");
    Joystick.setButton(decreaseButton, 1);
    Joystick.setButton(decreaseButton, 0);
  } else {
    Serial.println("increased");
    Joystick.setButton(increaseButton, 1);
    Joystick.setButton(increaseButton, 0);
  }
}

// DT, CLK
MyEncoder encoder1 (18, 19, [] (int8_t c) {
  encoderChange(c, 0, 1);
});
MyEncoder encoder2 (4, 5, [] (int8_t c) {
  encoderChange(c, 2, 3);
});
MyEncoder encoder3 (6, 7, [] (int8_t c) {
  encoderChange(c, 4, 5);
});
MyEncoder encoder4 (8, 9, [] (int8_t c) {
  encoderChange(c, 6, 7);
});
MyEncoder encoder5 (10, 16, [] (int8_t c) {
  encoderChange(c, 8, 9);
});
MyEncoder encoder6 (14, 15, [] (int8_t c) {
  encoderChange(c, 10, 11);
});

void setup() {
  Serial.begin(9600);
  mcp1.begin();
  Joystick.begin();
}

void loop() {
  encoder1.read();
  encoder2.read();
  encoder3.read();
  encoder4.read();
  encoder5.read();
  encoder6.read();
}
