#pragma once
#include "display.h"
#include "receiver.h"
#include <Arduino.h>

class Executor {
public:
  Executor(Display &disp);

  void execute(const Command &cmd);

private:
  Display &display;

  // Command handlers
  void handlePing();
  void handleHelp();
  void handleFwVersion();
  void handleClear();
  void handlePixel(uint8_t x, uint8_t y, uint8_t color);
  void handleRender(const uint8_t buffer[Display::NUM_COLS]);
};
