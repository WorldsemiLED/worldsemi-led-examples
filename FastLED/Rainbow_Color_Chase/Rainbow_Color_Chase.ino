#include <FastLED.h>

#define DATA_PIN    5
#define NUM_LEDS    30
#define BRIGHTNESS  96
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);
}

void rainbowEffect() {
  static uint8_t hue = 0;

  fill_rainbow(leds, NUM_LEDS, hue, 7);
  FastLED.show();

  hue++;
  delay(20);
}

void colorChase(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    FastLED.clear();
    leds[i] = color;
    FastLED.show();
    delay(40);
  }
}

void loop() {
  // Rainbow animation
  for (int i = 0; i < 300; i++) {
    rainbowEffect();
  }

  // Color chase animations
  colorChase(CRGB::Red);
  colorChase(CRGB::Green);
  colorChase(CRGB::Blue);
  colorChase(CRGB::White);
}
