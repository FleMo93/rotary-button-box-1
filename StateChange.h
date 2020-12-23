#ifndef StateChange_h
#define StateChange_h

#include <Arduino.h>

class StateChange
{
  private:
    bool _isStateTrue = false;
    bool (*_readState)();
    void (*_stateChangeCallback)(bool state);

  public:
    StateChange (
      bool readState(),
      void stateChangeCallback(bool state));

    void update();
};

#endif
