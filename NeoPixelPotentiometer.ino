#include <Adafruit_NeoPixel.h>

/*
  Control the brightness of an Adafruit NeoPixel
  using a potentiometer.
*/

const int PIXEL_PIN = 8; // NeoPixel input on digital 8.
const int POT_PIN = 0; // Potentiometer output on analog 0.

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int alpha = 0;
int reading = 0;

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.show();
}

void loop() {
  reading  = analogRead(POT_PIN);
  
  alpha = map(reading, 0, 1023, 0, 255);
  
  Serial.println(alpha);
  
  strip.setPixelColor(0, strip.Color(alpha, alpha, alpha));
  strip.show();
  
  delay(100);
}
