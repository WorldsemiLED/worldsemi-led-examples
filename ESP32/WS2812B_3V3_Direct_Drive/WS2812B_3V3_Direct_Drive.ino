#include <FastLED.h>

#define DATA_PIN    5
#define NUM_LEDS    8
#define BRIGHTNESS  80
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);
}

void loop() {
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(1000);

  FastLED.clear(true);
  delay(1000);
}
