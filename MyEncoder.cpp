#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Arduino.h>
//https://www.pjrc.com/teensy/td_libs_Encoder.html
#include <Encoder.h>
#include "MyEncoder.h"

MyEncoder::MyEncoder(
  uint8_t  DT,
  uint8_t  CLK,
  void (*rotaryCallback)(int8_t change)
) : _encoder{ DT, CLK },
  _rotaryCallback { rotaryCallback }
{
  _defaultPosition = _encoder.read();
  _position = _defaultPosition;
}

void MyEncoder::read()
{
  long newPosition = _encoder.read();
  //Serial.println(newPosition);

  if (newPosition == _position || (newPosition - _defaultPosition) % 4 != 0) {
    return;
  }

  if (newPosition > _position) {
    _rotaryCallback(1);
  } else {
    _rotaryCallback(-1);
  }

  _position = newPosition;
}
