#include "receiver.h"

Receiver::Receiver() : commandReady(false) { resetParser(); }

void Receiver::handleByte(uint8_t b) {
  if (b == '\n') {
    buffer.trim(); // remove trailing \r or spaces
    if (buffer.length() > 0) {
      parseCommandLine(buffer);
      commandReady = true;
    }
    buffer = "";
    return;
  }

  buffer += (char)b;

  // Prevent runaway memory
  if (buffer.length() > 128) {
    resetParser();
  }
}

bool Receiver::hasCommand() { return commandReady; }

Command Receiver::getCommand() {
  commandReady = false;
  return currentCommand; // return by value
}

void Receiver::resetParser() {
  buffer = "";
  currentCommand.valid = false;
  currentCommand.name = "";
  currentCommand.argCount = 0;
  for (uint8_t i = 0; i < MAX_ARGS; i++)
    currentCommand.args[i] = "";
}

void Receiver::parseCommandLine(const String &line) {
  currentCommand.valid = false;
  currentCommand.argCount = 0;

  uint16_t start = 0;
  int sepIndex = line.indexOf('|', start);

  if (sepIndex == -1) {
    currentCommand.name = line;
  } else {
    currentCommand.name = line.substring(0, sepIndex);
    start = sepIndex + 1;

    while (start < line.length() && currentCommand.argCount < MAX_ARGS) {
      int nextSep = line.indexOf('|', start);
      if (nextSep == -1)
        nextSep = line.length();
      currentCommand.args[currentCommand.argCount++] = line.substring(start, nextSep);
      start = nextSep + 1;
    }
  }
  currentCommand.valid = true;
}
