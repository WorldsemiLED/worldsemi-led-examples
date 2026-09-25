# WS2916A-RGBW Basic Control

This example is for the Worldsemi WS2916A-RGBW high-grayscale addressable RGBW LED.

## Key Features

- 5050 package
- RGBW integrated addressable LED
- 16-bit grayscale per channel
- 65536 grayscale levels per channel
- Up to 2 kHz refresh rate
- Single-wire RZ protocol
- Self-bypass function
- Adjustable current gain
- White-channel output greater than 15 lm

## Data Structure

Each refresh frame consists of:

1. 32-bit current-gain configuration data
2. 64-bit GRBW grayscale data for each pixel

Each pixel contains:

- Green: 16 bits
- Red: 16 bits
- Blue: 16 bits
- White: 16 bits

Data is transmitted in GRBW order, MSB first.

## Signal Timing

According to the WS2916A-RGBW specification:

- T0H: 220 ns to 380 ns
- T1H: 520 ns to 1 us
- Reset low time: > 280 us
- Data cycle: >= 1.25 us

## Hardware

- Arduino-compatible MCU or ESP32
- Worldsemi WS2916A-RGBW
- 5V LED power supply
- Common GND between MCU and LED power supply

## Wiring

| MCU | WS2916A-RGBW |
|---|---|
| Data GPIO | DIN |
| GND | GND |
| GND | BIN on first pixel |
| 5V | VDD |

The first pixel's BIN pin should not be left floating. Connect it to GND.

## 3.3V Logic

The WS2916A-RGBW input high-level threshold is specified as 0.55 × VDD.

With a 5V LED supply, this corresponds to approximately 2.75V, allowing a 3.3V MCU such as ESP32 to drive DIN directly.

## Important Thermal Note

Do not operate the White channel at maximum brightness simultaneously with RGB at maximum brightness.

Refer to the latest WS2916A-RGBW datasheet for power and thermal limits.

## Software

A protocol-specific example will be provided for:

- 32-bit current-gain transmission
- 64-bit GRBW pixel transmission
- 16-bit grayscale control
- Basic RGBW output
- White-channel brightness control

## Links

Worldsemi:
https://www.world-semi.com

YouTube:
https://www.youtube.com/@WorldsemiLED

Reddit:
https://www.reddit.com/user/WorldsemiLED/

LinkedIn:
https://www.linkedin.com/in/yinhuaping
