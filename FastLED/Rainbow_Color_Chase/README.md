# FastLED Rainbow & Color Chase — Worldsemi WS2812B

This example demonstrates two simple FastLED effects using Worldsemi WS2812B addressable LEDs:

- Rainbow animation
- Single-pixel color chase

## Hardware

- ESP32 or Arduino-compatible development board
- Worldsemi WS2812B or compatible addressable LEDs
- Suitable LED power supply
- Common GND between MCU and LED power supply

## Wiring

| MCU | Worldsemi LED |
|---|---|
| GPIO 5 | DIN |
| GND | GND |

Connect the LED VDD to the appropriate supply voltage for the selected Worldsemi device.

## Software

Install the FastLED library before compiling this example.

This example uses:

```cpp
FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
