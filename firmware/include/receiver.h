#pragma once
#include <Arduino.h>

#define MAX_ARGS 20
struct Command {
  String name;
  String args[MAX_ARGS]; // up to 10 arguments
  uint8_t argCount;
  bool valid;
};

class Receiver {
public:
  Receiver();

  void handleByte(uint8_t b); // feed a byte from polling
  bool hasCommand();          // Is a command ready?
  Command getCommand();       // Fetch command by value

private:
  String buffer;
  Command currentCommand;
  bool commandReady;

  void resetParser();
  void parseCommandLine(const String &line);
};
