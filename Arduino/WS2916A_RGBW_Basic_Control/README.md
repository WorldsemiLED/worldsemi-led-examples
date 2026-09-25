# WS2916A-RGBW Basic Control

This example is for the Worldsemi WS2916A-RGBW high-grayscale addressable RGBW LED.

## Key Features

- Operating voltage: 3.3V–5.5V
- RGB current: up to 30mA
- White-channel current: up to 60mA
- Configurable white CCT: 2700K–7000K
- Single-wire self-bypass protocol
- 5-bit per-channel current gain
- 16-bit grayscale data per RGBW channel
- 96-bit total data per pixel
- 5050 package
- White-channel output greater than 15 lm

## Pixel Data Format

WS2916A-RGBW uses a 96-bit pixel data structure.

The protocol includes:

- Per-channel current-gain configuration
- Parity / control data
- 16-bit Red data
- 16-bit Green data
- 16-bit Blue data
- 16-bit White data

Because this device uses a different data format from standard 24-bit WS2812B devices, standard WS2812B libraries should not be assumed to work without protocol support.

## Hardware

- Arduino-compatible MCU or ESP32
- Worldsemi WS2916A-RGBW
- Appropriate LED power supply
- Common GND between MCU and LED power supply

## Wiring

| MCU | WS2916A-RGBW |
|---|---|
| Data GPIO | DIN |
| GND | GND |

Connect VDD according to the target application and WS2916A-RGBW specification.

## Software

A protocol-specific example will be added here for:

- 96-bit pixel transmission
- RGBW 16-bit grayscale control
- Per-channel current-gain settings
- Basic RGBW color output
- White-channel brightness control

## Notes

Do not use a standard 24-bit WS2812B data routine for this device.

Always refer to the latest WS2916A-RGBW datasheet and protocol specification.

## Links

Worldsemi:  
https://www.world-semi.com

YouTube:  
https://www.youtube.com/@WorldsemiLED

Reddit:  
https://www.reddit.com/user/WorldsemiLED/

LinkedIn:  
https://www.linkedin.com/in/yinhuaping
