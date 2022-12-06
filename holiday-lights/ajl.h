#include <math.h>



void snowing(CRGB *leds)
{
  const double bottomLightCount = 31.3;
  const double topLightCount = 5.0;
  const double lightRate = 1.0;
  double theta = 0;
  theta = (int(gLoopCounter * lightRate)) % 360;
  double thetaPercent = theta / 360;
  for (double z = 0; z <= 1.0; z = z + 0.03)
  {
    int lightRingTotal = round(z * (bottomLightCount - topLightCount) + topLightCount);
    int lightIndex = round((thetaPercent * lightRingTotal) + (z * NUM_LEDS));
    leds[lightIndex] = CRGB::Blue;
  }
  fadeToBlackBy( leds, NUM_LEDS, 20);
}

void snowing()
{
  snowing(leds1);
  snowing(leds2);
  snowing(leds3);
}

