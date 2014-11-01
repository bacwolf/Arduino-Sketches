#include <Adafruit_NeoPixel.h>

/*
  Uses Adafruit NeoPixels to display ambient green light
  with intermittent white flashes to simulate lightning.
  Uses 16 NeoPixels by default.
  
  Hastily-assembled for some Halloween lighting.
*/

const int PIXEL_PIN = 1; // NeoPixel input.

const int STATE_IDLE = 0;
const int STATE_FLASH_SHORT = 1;
const int STATE_DARK = 2;
const int STATE_FLASH_LONG = 3;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int sequence[] = {
  STATE_IDLE,
  STATE_FLASH_SHORT,
  STATE_DARK,
  STATE_FLASH_LONG,
  STATE_DARK,
  STATE_FLASH_SHORT,
  STATE_DARK
};

unsigned int sequenceLength;
unsigned int sequencePosition;
unsigned long lastStateChangeTime;

void setup() {
  strip.begin();
  
  sequenceLength = (sizeof(sequence)/sizeof(int));
  sequencePosition = 0;
  
  setState(sequence[sequencePosition]);
}

void loop() {
  long timeElapsed = (millis() - lastStateChangeTime);
  
  // Check for enough time elapsed to move to next sequence position.
  if (timeElapsed >= getStateLength(sequence[sequencePosition])) {
    // Check for end of sequence. sequenceLength -1 due to zero-indexed array.
    if (sequencePosition < (sequenceLength - 1)) {
      // Increment sequence position until end of sequence is reached.
      sequencePosition++;
    }
    else {
      // Reset the sequence to the beginning.
      sequencePosition = 0;
    }
    
    // Set the state based on the current sequence position.
    setState(sequence[sequencePosition]);
  }
}

/**
 * Sets the state of the pixels, causing them to adopt
 * a color for a period of time.
 */
void setState(int newState) {
  uint32_t color;
  
  switch (newState) {
    case STATE_IDLE:
      color = strip.Color(0, 255, 0);
      break;
    case STATE_FLASH_SHORT:
      color = strip.Color(100, 255, 100);
      break;
    case STATE_DARK:
      color = strip.Color(0, 100, 0);
      break;
    case STATE_FLASH_LONG:
      color = strip.Color(255, 255, 255);
      break;
    default:
      color = strip.Color(0, 0, 0);
      break;
  }
  
  lastStateChangeTime = millis();
  
  setPixelsColor(color);
}

/**
 * Gets the length of a given state in milliseconds.
 */
long getStateLength(int state) {
  long length = 0;
  
  switch (state) {
    case STATE_IDLE:
      length = 30000;
      break;
    case STATE_FLASH_SHORT:
      length = 50;
      break;
    case STATE_DARK:
      length = 100;
      break;
    case STATE_FLASH_LONG:
      length = 200;
      break;
  }
  
  return length;
}

/**
 * Sets the color of all pixels.
 */
void setPixelsColor(uint32_t color) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  
  strip.show();
}
