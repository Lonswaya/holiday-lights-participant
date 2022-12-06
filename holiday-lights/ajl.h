#include <math.h>

const double BOTTOM_LIGHT_COUNT = 31.3;
const double TOP_LIGHT_COUNT = 5.0;
const double LIGHT_SPEED = 1.0;
const double LIGHT_SPREAD_MULT = 0.75;

int lightRingCount(int startIndex)
{
  // lerp
  return round((BOTTOM_LIGHT_COUNT + (startIndex / NUM_LEDS) * (TOP_LIGHT_COUNT - BOTTOM_LIGHT_COUNT)) * LIGHT_SPREAD_MULT);
}

void snowing(CRGB *leds)
{
  double theta = 0;
  theta = (int(gLoopCounter * LIGHT_SPEED)) % 360;
  double thetaPercent = theta / 360;
  //double z = 0.5
  for (int start = 0; start < NUM_LEDS; start = start + lightRingCount(start))
  {
    int nextStep = lightRingCount(start);
    if (start + round(nextStep * thetaPercent) < NUM_LEDS)
    {
      leds[start + int(round(double(nextStep) * thetaPercent))] = CRGB::Blue;
    }
    //if (start <= z < nextStep)
    //{
      
    //}
  }
  fadeToBlackBy( leds, NUM_LEDS, 20);
}

void snowing()
{
  snowing(leds1);
  snowing(leds2);
  snowing(leds3);
}

