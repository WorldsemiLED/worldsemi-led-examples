#include <Arduino.h>
#include "esp32-hal-rmt.h"

// ---------------------------------------------------------
// Worldsemi WS2916A-RGBW Basic Control Example
// ESP32 Arduino Core 3.x
//
// Frame:
//   32-bit current-gain header
//   + 64-bit GRBW data per pixel
//   + RESET low > 280 us
//
// Bit order: MSB first
// ---------------------------------------------------------

#define DATA_PIN 5
#define NUM_LEDS 1

// RMT resolution: 10 MHz = 100 ns per tick
#define RMT_FREQ_HZ 10000000

// WS2916A timing
// 0: 300 ns HIGH + 1000 ns LOW = 1.3 us
// 1: 700 ns HIGH + 600 ns LOW  = 1.3 us
#define T0H_TICKS 3
#define T0L_TICKS 10
#define T1H_TICKS 7
#define T1L_TICKS 6

struct RGBW16 {
  uint16_t g;
  uint16_t r;
  uint16_t b;
  uint16_t w;
};

RGBW16 pixels[NUM_LEDS];

// ---------------------------------------------------------
// Build 32-bit current-gain header
//
// G gain: 5 bits
// R gain: 5 bits
// B gain: 5 bits
// W gain: 5 bits
// Remaining 12 bits: fixed to 1
// ---------------------------------------------------------
uint32_t makeGainHeader(
  uint8_t gainG,
  uint8_t gainR,
  uint8_t gainB,
  uint8_t gainW
) {
  gainG &= 0x1F;
  gainR &= 0x1F;
  gainB &= 0x1F;
  gainW &= 0x1F;

  return ((uint32_t)gainG << 27) |
         ((uint32_t)gainR << 22) |
         ((uint32_t)gainB << 17) |
         ((uint32_t)gainW << 12) |
         0x0FFF;
}

// ---------------------------------------------------------
// Convert one protocol bit to one RMT symbol
// ---------------------------------------------------------
rmt_data_t makeBit(bool bitValue) {
  rmt_data_t symbol;

  if (bitValue) {
    symbol.duration0 = T1H_TICKS;
    symbol.level0 = 1;
    symbol.duration1 = T1L_TICKS;
    symbol.level1 = 0;
  } else {
    symbol.duration0 = T0H_TICKS;
    symbol.level0 = 1;
    symbol.duration1 = T0L_TICKS;
    symbol.level1 = 0;
  }

  return symbol;
}

// ---------------------------------------------------------
// Append data MSB first
// ---------------------------------------------------------
void appendBits(
  rmt_data_t *buffer,
  size_t &index,
  uint32_t value,
  uint8_t bitCount
) {
  for (int bit = bitCount - 1; bit >= 0; bit--) {
    buffer[index++] = makeBit((value >> bit) & 0x01);
  }
}

void append16(
  rmt_data_t *buffer,
  size_t &index,
  uint16_t value
) {
  appendBits(buffer, index, value, 16);
}

// ---------------------------------------------------------
// Send one complete WS2916A-RGBW frame
// ---------------------------------------------------------
void showWS2916A(
  uint8_t gainG,
  uint8_t gainR,
  uint8_t gainB,
  uint8_t gainW
) {
  const size_t symbolCount = 32 + (NUM_LEDS * 64);

  static rmt_data_t symbols[32 + (NUM_LEDS * 64)];

  size_t index = 0;

  // 1. Current-gain frame header
  uint32_t gainHeader =
    makeGainHeader(gainG, gainR, gainB, gainW);

  appendBits(symbols, index, gainHeader, 32);

  // 2. Pixel data: GRBW, 16 bits each, MSB first
  for (int i = 0; i < NUM_LEDS; i++) {
    append16(symbols, index, pixels[i].g);
    append16(symbols, index, pixels[i].r);
    append16(symbols, index, pixels[i].b);
    append16(symbols, index, pixels[i].w);
  }

  // Ensure reset before frame
  delayMicroseconds(300);

  rmtWrite(
    DATA_PIN,
    symbols,
    symbolCount,
    RMT_WAIT_FOR_EVER
  );

  // RESET > 280 us
  delayMicroseconds(300);
}

// ---------------------------------------------------------
// Set all pixels
// ---------------------------------------------------------
void setAll(
  uint16_t r,
  uint16_t g,
  uint16_t b,
  uint16_t w
) {
  for (int i = 0; i < NUM_LEDS; i++) {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
    pixels[i].w = w;
  }
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW);

  // Initialize ESP32 RMT transmitter
  if (!rmtInit(
        DATA_PIN,
        RMT_TX_MODE,
        RMT_MEM_NUM_BLOCKS_1,
        RMT_FREQ_HZ)) {
    while (true) {
      delay(1000);
    }
  }

  rmtSetEOT(DATA_PIN, LOW);

  delay(500);
}

void loop() {

  // Use moderate current gain for demonstration.
  // Range: 0-31.
  const uint8_t gainRGB = 10;
  const uint8_t gainW   = 10;

  // RED
  setAll(65535, 0, 0, 0);
  showWS2916A(gainRGB, gainRGB, gainRGB, gainW);
  delay(1000);

  // GREEN
  setAll(0, 65535, 0, 0);
  showWS2916A(gainRGB, gainRGB, gainRGB, gainW);
  delay(1000);

  // BLUE
  setAll(0, 0, 65535, 0);
  showWS2916A(gainRGB, gainRGB, gainRGB, gainW);
  delay(1000);

  // WHITE CHANNEL
  setAll(0, 0, 0, 32768);
  showWS2916A(gainRGB, gainRGB, gainRGB, gainW);
  delay(1000);

  // RGB + moderate white
  setAll(16384, 16384, 16384, 8192);
  showWS2916A(gainRGB, gainRGB, gainRGB, gainW);
  delay(1000);

  // OFF
  setAll(0, 0, 0, 0);
  showWS2916A(gainRGB, gainRGB, gainRGB, gainW);
  delay(1000);
}
