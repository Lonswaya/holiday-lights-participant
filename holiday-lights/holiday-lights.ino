#include <FastLED.h>

#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>

FASTLED_USING_NAMESPACE

// General LED Set Up
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

// for pinout, see https://learn.adafruit.com/assets/111179

// LED Strip Set Up 
#define LED1_PIN    21
#define LED2_PIN    16
#define LED3_PIN    17
#define NUM_LEDS 300
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  Serial.println("in setup");

  delay(3000); // 3 second delay for recovery

  FastLED.addLeds<LED_TYPE,LED1_PIN,COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,LED2_PIN,COLOR_ORDER>(leds2, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,LED3_PIN,COLOR_ORDER>(leds3, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint16_t gLoopCounter = 0;
  
////////////////////////////////////
// include participant files
#include "samples.h"
#include "ajl.h"
////////////////////////////////////

void loop()
{
  // this is where you call your function, instead of the sample
  snowing();

  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 20 )
  {
    gLoopCounter = 0;
    gHue = 0;
    FastLED.clear();
    FastLED.show();
    delay(1500);
  }

  gLoopCounter++;
}
