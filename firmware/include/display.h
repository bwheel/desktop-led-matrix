#pragma once
#include <Adafruit_GFX.h>
#include <Arduino.h>

class Display : public Adafruit_GFX {
public:
  static const uint8_t NUM_COLS = 20;
  static const uint8_t NUM_ROWS = 7;

  Display();
  void begin();
  void drawPixel(int16_t x, int16_t y, uint16_t color) override;
  void clear();
  void swap();
  void renderBuffer(const uint8_t buffer[NUM_COLS]);

private:
  volatile uint8_t displayBuffer[NUM_COLS]; // ISR reads from here
  uint8_t drawBuffer[NUM_COLS];             // Main code writes here
  volatile uint8_t currentCol;

  static Display *instance;
  static void refreshISR();
  void refresh();
};
