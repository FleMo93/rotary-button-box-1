#ifndef MyEncoder_h
#define MyEncoder_h

#include <Arduino.h>
#include <Encoder.h>

class MyEncoder
{
  private:
    Encoder _encoder;
    void (*_rotaryCallback)(int8_t);
    long _defaultPosition;
    long _position = 999;
    bool _isDecreasing = false;
    bool _isIncreasing = true;

  public:
    MyEncoder (
      uint8_t DT,
      uint8_t CLK,
      void rotaryCallback(int8_t change));

    void read();
};

#endif
