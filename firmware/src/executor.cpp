#include "executor.h"

Executor::Executor(Display &disp) : display(disp) {}

void Executor::execute(const Command &cmd) {
  if (!cmd.valid)
    return;

  if (cmd.name == "PING")
    handlePing();
  else if (cmd.name == "HELP") {
    handleHelp();
  } else if (cmd.name == "FWVERSION") {
    Serial.println("Firmware Version 1.0");
  } else if (cmd.name == "CLEAR")
    handleClear();
  else if (cmd.name == "PIXEL") {
    if (cmd.argCount < 3) {
      Serial.println("ERR: PIXEL requires 3 arguments");
      return;
    }
    uint8_t x = cmd.args[0].toInt();
    uint8_t y = cmd.args[1].toInt();
    uint8_t color = cmd.args[2].toInt();
    handlePixel(x, y, color);
  } else if (cmd.name == "RENDER") {
    if (cmd.argCount < Display::NUM_COLS) {
      Serial.println("ERR: RENDER requires " + String(Display::NUM_COLS) + " arguments");
      return;
    }
    uint8_t buffer[Display::NUM_COLS];
    for (uint8_t i = 0; i < Display::NUM_COLS; i++) {
      buffer[i] = cmd.args[i].toInt();
    }
    handleRender(buffer);
  } else {
    Serial.println("ERR: Unknown command " + cmd.name);
  }
}

void Executor::handlePing() { Serial.println("PONG"); }

void Executor::handleHelp() {
  Serial.println("Available commands:");
  Serial.println("PING - Check if the device is responsive");
  Serial.println("HELP - List available commands");
  Serial.println("FWVERSION - Get firmware version");
  Serial.println("CLEAR - Clear the display");
  Serial.println("PIXEL|<x>|<y>|<color> - Set pixel at (x,y) to color (0 or 1)");
  Serial.println("RENDER|<col1>|<col2>|...|<col20> - Render the full display buffer");
}

void Executor::handleClear() {
  display.clear();
  display.swap();
}

void Executor::handlePixel(uint8_t x, uint8_t y, uint8_t color) {
  display.drawPixel(x, y, color ? 1 : 0);
  display.swap();
}

void Executor::handleRender(const uint8_t buffer[Display::NUM_COLS]) {
  display.renderBuffer(buffer);
  display.swap();
}
