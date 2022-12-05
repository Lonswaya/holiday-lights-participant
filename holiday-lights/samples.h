void straightYesChaserInternal(CRGB *leds, CRGB color)
{
  leds[gLoopCounter % NUM_LEDS] = color;
  fadeToBlackBy( leds, NUM_LEDS, 20);
}

void straightYesChaser()
{
  straightYesChaserInternal(leds1, CRGB::Red);
  straightYesChaserInternal(leds2, CRGB::Blue);
  straightYesChaserInternal(leds3, CRGB::Green);
}

void confettiEach(CRGB *leds)
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void confetti() 
{
  confettiEach(leds1);
  confettiEach(leds2);
  confettiEach(leds3);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds1, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds1[pos] += CHSV( gHue, 255, 192);
  leds2[pos] += CHSV( gHue, 255, 192);
  leds3[pos] += CHSV( gHue, 255, 192);
}

void addGlitter( fract8 chanceOfGlitter, CRGB *leds) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  // FastLED's built-in rainbow generator
  fill_rainbow(leds1, NUM_LEDS, gHue, 7);
  fill_rainbow(leds2, NUM_LEDS, gHue, 7);
  fill_rainbow(leds3, NUM_LEDS, gHue, 7);
  addGlitter(80, leds1);
  addGlitter(80, leds2);
  addGlitter(80, leds3);
}
