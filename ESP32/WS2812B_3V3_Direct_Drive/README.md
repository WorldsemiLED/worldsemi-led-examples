# ESP32 3.3V Direct Drive — Worldsemi WS2812B

This example demonstrates direct control of a Worldsemi addressable LED from an ESP32 3.3V GPIO without an external logic-level shifter.

## Hardware

- ESP32 development board
- Worldsemi WS2812B or compatible 3.3V-logic addressable LED
- LED power supply suitable for the selected LED
- Common GND between ESP32 and LED power supply

## Wiring

| ESP32 | Worldsemi LED |
|---|---|
| GPIO 5 | DIN |
| GND | GND |

Connect the LED VDD to the appropriate supply voltage for the specific Worldsemi device being used.

A small series resistor on DIN and local decoupling capacitor may be added depending on wiring length and application requirements.

## Why 3.3V Direct Drive?

Many ESP32 boards output 3.3V logic.

New-generation Worldsemi addressable LEDs are designed for reliable operation with 3.3V MCU logic, allowing direct connection from an ESP32 GPIO to DIN without an external 5V logic-level shifter.

This can simplify:

- PCB design
- BOM cost
- Board area
- Wiring
- Prototype development

## Software

Install the FastLED library in the Arduino IDE.

This example uses:

```cpp
FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
