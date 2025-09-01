#include "display.h"
#include <TimerOne.h>
#include <string.h>

Display *Display::instance = nullptr;

Display::Display() : Adafruit_GFX(NUM_COLS, NUM_ROWS), currentCol(0) {
  memset((void *)displayBuffer, 0, NUM_COLS);
  memset(drawBuffer, 0, NUM_COLS);
  instance = this;
}

void Display::begin() {
  // Rows PB0-PB6
  DDRB |= 0x7F;
  PORTB &= ~0x7F;

  // Address bits PD4-PD6
  DDRD |= 0x70;

  // Select lines PC2, PC3
  DDRC |= (1 << PC2) | (1 << PC3);

  // Timer1 ISR
  Timer1.initialize(100); // ~100µs per column
  Timer1.attachInterrupt(Display::refreshISR);
}

void Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (x < 0 || x >= NUM_COLS || y < 0 || y >= NUM_ROWS)
    return;
  if (color)
    drawBuffer[x] |= (1 << y);
  else
    drawBuffer[x] &= ~(1 << y);
}

void Display::clear() { memset(drawBuffer, 0, NUM_COLS); }

void Display::swap() {
  noInterrupts();
  memcpy((void *)displayBuffer, drawBuffer, NUM_COLS);
  interrupts();
}

void Display::renderBuffer(const uint8_t buffer[NUM_COLS]) { memcpy(drawBuffer, buffer, NUM_COLS); }

void Display::refreshISR() {
  if (instance)
    instance->refresh();
}

void Display::refresh() {
  uint8_t col = currentCol;
  uint8_t data = displayBuffer[col];

  PORTB &= ~0x7F;
  PORTB |= (data & 0x7F);

  uint8_t addr = col & 0x07;
  PORTD = (PORTD & 0x0F) | (addr << 4);

  if (col < 8)
    PORTC = (PORTC & ~((1 << PC2) | (1 << PC3))) | (1 << PC2);
  else if (col < 16)
    PORTC = (PORTC & ~((1 << PC2) | (1 << PC3))) | (1 << PC3);
  else
    PORTC &= ~((1 << PC2) | (1 << PC3));

  currentCol = (currentCol + 1) % NUM_COLS;
}
