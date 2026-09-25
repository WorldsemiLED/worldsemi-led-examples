# WS2916A-RGBW Basic Control

This example demonstrates basic control of the Worldsemi WS2916A-RGBW high-grayscale addressable RGBW LED using an ESP32.

## Key Features

- 5050 RGBW addressable LED
- Single-wire RZ protocol
- Self-bypass function
- 16-bit grayscale per channel
- 65536 grayscale levels per channel
- Up to 2 kHz refresh rate
- Adjustable current gain
- GRBW data order
- White-channel output greater than 15 lm

## Frame Structure

Each refresh frame consists of:

1. One 32-bit current-gain header
2. 64-bit GRBW grayscale data for each pixel
3. Reset low time greater than 280 us

### 32-bit Current-Gain Header

The 32-bit frame header contains:

- Green current gain: 5 bits
- Red current gain: 5 bits
- Blue current gain: 5 bits
- White current gain: 5 bits
- Remaining 12 control bits: set to logic 1

Current-gain range:

- 0 to 31 for each channel

## Pixel Data

Each WS2916A-RGBW pixel receives 64 bits:

- Green: 16 bits
- Red: 16 bits
- Blue: 16 bits
- White: 16 bits

Data order:

GRBW

Bit order:

MSB first

## Signal Timing

Typical timing used in this ESP32 example:

| Signal | Timing |
|---|---|
| T0H | 300 ns |
| T1H | 700 ns |
| Bit period | approximately 1.3 us |
| Reset LOW | 300 us |

These values are selected within the WS2916A-RGBW timing specification.

## Hardware

- ESP32 development board
- Worldsemi WS2916A-RGBW
- 5V LED power supply
- Common GND between ESP32 and LED power supply

## Wiring

| ESP32 / Power | WS2916A-RGBW |
|---|---|
| GPIO 5 | DIN |
| GND | GND |
| GND | BIN of the first pixel |
| +5V | VDD |

The BIN pin of the first WS2916A-RGBW should not be left floating. Connect it to GND.

## 3.3V Logic Compatibility

The WS2916A-RGBW input high-level threshold is specified as:

0.55 × VDD

With a 5V LED supply, the input high-level threshold is approximately 2.75V.

This allows a 3.3V ESP32 GPIO signal to drive DIN directly without an external 5V logic-level shifter.

## ESP32 RMT

This example uses the ESP32 RMT peripheral to generate accurate single-wire timing.

The RMT peripheral is used to transmit:

- 32-bit current-gain header
- 64-bit GRBW data per pixel
- MSB-first data
- Precise WS2916A-RGBW timing

## Basic Demo Sequence

The example cycles through:

1. Red
2. Green
3. Blue
4. White channel
5. RGB + moderate White
6. Off

## Thermal Note

The White channel should not be operated at maximum brightness simultaneously with RGB at maximum brightness.

Use appropriate current gain and grayscale settings for the thermal requirements of the application.

For initial testing, moderate current-gain settings are recommended.

## Files

- `WS2916A_RGBW_Basic_Control.ino` — ESP32 RMT example
- `README.md` — documentation and wiring information

## Links

Worldsemi  
https://www.world-semi.com

YouTube  
https://www.youtube.com/@WorldsemiLED

Reddit  
https://www.reddit.com/user/WorldsemiLED/

LinkedIn  
https://www.linkedin.com/in/yinhuaping
