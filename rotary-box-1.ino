#include <Wire.h>
#include <Adafruit_MCP23017.h>

#include <Joystick.h>
#include "MyEncoder.h"
#include "StateChange.h"

//https://github.com/MHeironimus/ArduinoJoystickLibrary
Joystick_ Joystick(0x04, 0x05, 18, 0, false, false, false, false, false, false, false, false, false, false, false);
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

void buttonChange(int8_t buttonNumber, bool change) {
  if (change) {
    Joystick.setButton(buttonNumber, 1);
    Serial.println("button down");
  } else {
    Joystick.setButton(buttonNumber, 0);
    Serial.println("button up");
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

const int numberOfEncoderButtons = 6;
StateChange ecnoderButtons[] = {
  StateChange ([] () {
    return mcp1.digitalRead(8) == LOW;
  }, [] (bool state) {
    buttonChange(12, state);
  }),
  StateChange ([] () {
    return mcp1.digitalRead(9) == LOW;
  }, [] (bool state) {
    buttonChange(13, state);
  }),
  StateChange ([] () {
    return mcp1.digitalRead(10) == LOW;
  }, [] (bool state) {
    buttonChange(14, state);
  }),
  StateChange ([] () {
    return mcp1.digitalRead(11) == LOW;
  }, [] (bool state) {
    buttonChange(15, state);
  }),
  StateChange ([] () {
    return mcp1.digitalRead(12) == LOW;
  }, [] (bool state) {
    buttonChange(16, state);
  }),
  StateChange ([] () {
    return mcp1.digitalRead(13) == LOW;
  }, [] (bool state) {
    buttonChange(17, state);
  })
};

byte rows[] = {0, 1, 2, 3};
byte cols[] = {4, 5, 6, 7};
const byte rowCount = sizeof(rows) / sizeof(rows[0]);
const byte colCount = sizeof(cols) / sizeof(cols[0]);

void setup() {
  Serial.begin(9600);
  mcp1.begin();

  mcp1.pinMode(8, INPUT);
  mcp1.pullUp(8, HIGH);
  mcp1.pinMode(9, INPUT);
  mcp1.pullUp(9, HIGH);
  mcp1.pinMode(10, INPUT);
  mcp1.pullUp(10, HIGH);
  mcp1.pinMode(11, INPUT);
  mcp1.pullUp(11, HIGH);
  mcp1.pinMode(12, INPUT);
  mcp1.pullUp(12, HIGH);
  mcp1.pinMode(13, INPUT);
  mcp1.pullUp(13, HIGH);

  for (int y = 0; y < rowCount; y++) {
    mcp1.pinMode(rows[y], INPUT);
  }

  for (int x = 0; x < colCount; x++) {
    mcp1.pinMode(cols[x], INPUT);
    mcp1.pullUp(cols[x], HIGH);
  }

  Joystick.begin();
}

void loopEncoder() {
  encoder1.read();
  encoder2.read();
  encoder3.read();
  encoder4.read();
  encoder5.read();
  encoder6.read();
}


void loopEncoderButtons() {
  for (int i = 0; i < numberOfEncoderButtons; i++) {
    ecnoderButtons[i].update();
  }
}

void loopButtonArray() {
  for (int colIndex = 0; colIndex < colCount; colIndex++) {
    byte curCol = cols[colIndex];
    mcp1.pinMode(curCol, OUTPUT);
    mcp1.digitalWrite(curCol, LOW);

    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
      byte rowCol = rows[rowIndex];
      mcp1.pullUp(rowCol, HIGH);

      if (mcp1.digitalRead(rowCol) == LOW) {
        Serial.print("1");
      } else {
        Serial.print("0");
      }

      mcp1.pullUp(rowCol, LOW);
    }

    mcp1.pinMode(curCol, INPUT);
  }
  Serial.println("");
}

void loop() {
  loopEncoder();
  loopEncoderButtons();
  loopButtonArray();
}
