#include <Adafruit_NeoPixel.h>

/*
  Causes Adafruit NeoPixels to continuously fade between two colors.
  Fades two NeoPixels between opposing colors by default.
*/

const int PIXEL_PIN = 8; // NeoPixel input on digital 8.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

uint32_t color1 = strip.Color(210, 0, 255); // Purple.
uint32_t color2 = strip.Color(0, 156, 255); // Blue.

uint32_t pixel1_color, pixel2_color, pixel1_target_color, pixel2_target_color;

// The difference applied to each RGB value every loop. Controls the fade speed.
uint8_t fade_delta;
// The delay between applying the fade delta in milliseconds.
uint8_t fade_delay;

void setup() {
  pixel1_color = color1;
  pixel2_color = color2;

  pixel1_target_color = color2;
  pixel2_target_color = color1;

  fade_delta = 1;
  fade_delay = 100;

  strip.begin();
  strip.setPixelColor(0, pixel1_color);
  strip.show();
}

void loop() {
  // Fade current colors towards target colors.
  pixel1_color = fadeColor(pixel1_color, pixel1_target_color, fade_delta);
  strip.setPixelColor(0, pixel1_color);

  pixel2_color = fadeColor(pixel2_color, pixel2_target_color, fade_delta);
  strip.setPixelColor(1, pixel2_color);

  strip.show();

  // Reverse target colors once a color has been reached.
  if (pixel1_color == pixel1_target_color) {
    pixel1_target_color = (pixel1_target_color == color1) ? color2 : color1;
  }

  if (pixel2_color == pixel2_target_color) {
    pixel2_target_color = (pixel2_target_color == color1) ? color2 : color1;
  }

  delay(fade_delay);
}

uint32_t fadeColor(uint32_t color, uint32_t target_color, uint8_t delta) {
  uint8_t r = (uint8_t) (color >> 16),
    g = (uint8_t) (color >> 8),
    b = (uint8_t) color,
    target_r = (uint8_t) (target_color >> 16),
    target_g = (uint8_t) (target_color >> 8),
    target_b = (uint8_t) target_color;

    r = updateColorRGBValue(r, target_r, fade_delta);
    g = updateColorRGBValue(g, target_g, fade_delta);
    b = updateColorRGBValue(b, target_b, fade_delta);

    return strip.Color(r, g, b);
}

uint8_t updateColorRGBValue(uint8_t value, uint8_t target_value, uint8_t delta) {
  if (target_value > value) {
    value += delta;
    if (value > target_value) {
      value = target_value;
    }
  }
  else if (target_value < value) {
    value -= delta;
    if (value < target_value) {
      value = target_value;
    }
  }

  return value;
}
