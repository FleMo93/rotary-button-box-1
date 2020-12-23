#include <Arduino.h>
#include "StateChange.h"

StateChange::StateChange(
  bool readState(),
  void stateChangeCallback(bool state)
) : _stateChangeCallback { stateChangeCallback },
  _readState { readState }
{ }

void StateChange::update() {
  bool state = _readState();
  if (state == _isStateTrue) {
    return;
  }
  _stateChangeCallback(state);
  _isStateTrue = state;
}
