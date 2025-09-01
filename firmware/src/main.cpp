#include "display.h"
#include "executor.h"
#include "receiver.h"
#include <Arduino.h>

Display display;
Receiver receiver;
Executor executor(display);

void setup() {
  Serial.begin(115200);
  display.begin();
}

void loop() {
  while (Serial.available()) {
    uint8_t b = Serial.read();
    receiver.handleByte(b);
    Serial.write(b); // Echo back
  }
  if (receiver.hasCommand()) {
    Command cmd = receiver.getCommand();
    executor.execute(cmd);
  }
}
