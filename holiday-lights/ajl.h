#include <math.h>
#include <stdlib.h>     /* srand, rand */

const double BOTTOM_LIGHT_COUNT = 31.3;
const double TOP_LIGHT_COUNT = 5.0;
const double LIGHT_SPEED = 1.0;
const double LIGHT_SPREAD_MULT = 0.75;

int lightRingCount(int startIndex)
{
  // lerp
  return round((BOTTOM_LIGHT_COUNT + (startIndex / NUM_LEDS) * (TOP_LIGHT_COUNT - BOTTOM_LIGHT_COUNT)) * LIGHT_SPREAD_MULT);
}

int thetaAndZToIndex(double theta, double z)
{
  /*
  double thetaPercent = theta / 360;
  for (int start = 0; start < NUM_LEDS; start = start + lightRingCount(start))
    {
      int nextStep = lightRingCount(start);
      int possibleIndex = start + int(round(double(nextStep) * thetaPercent));
      Serial.print(gLoopCounter);
      Serial.print(" is loop counter ");
      Serial.print(z);
      Serial.print(" is z, ");
      Serial.print(possibleIndex);
      Serial.print(" is possibleIndex, and then lowerBound is ");
      Serial.println(double(start) / double(NUM_LEDS));
      if (possibleIndex < NUM_LEDS && (double(start) / double(NUM_LEDS)) < z && z < double(start + nextStep)/double(NUM_LEDS))
      {
        return possibleIndex;
      }
    }
  return NUM_LEDS - 1;*/

  /*int thetaOffset = (theta/360) * (1 - z);
  int possibleIndex = (z * NUM_LEDS) + thetaOffset;
  if (possibleIndex >= NUM_LEDS)
  {
    return NUM_LEDS - 1;
  }
  return possibleIndex;*/

  // TODO do if gates from 0 to 16
  int z_scaled = round(z * 16);
  int targetIndex = 0;
  double thetaPercent = theta / 360;
  switch (z_scaled)
  {
    case 0:
      targetIndex = 0 + (thetaPercent * 31);
      break;
    case 1:
      targetIndex = 31 + (thetaPercent * 30);
      break;
    case 2:
      targetIndex = 61 + (thetaPercent * 28);
      break;
    case 3:
      targetIndex = 89 + (thetaPercent * 27);
      break;
    case 4:
      targetIndex = 116 + (thetaPercent * 26);
      break;
    case 5:
      targetIndex = 142 + (thetaPercent * 24);
      break;
    case 6:
      targetIndex = 166 + (thetaPercent * 23);
      break;
    case 7:
      targetIndex = 189 + (thetaPercent * 21);
      break;
    case 8:
      targetIndex = 210 + (thetaPercent * 19);
      break;
    case 9:
      targetIndex = 229 + (thetaPercent * 17);
      break;
    case 10:
      targetIndex = 246 + (thetaPercent * 15);
      break;
    case 11:
      targetIndex = 261 + (thetaPercent * 12);
      break;
    case 12:
      targetIndex = 273 + (thetaPercent * 11);
      break;
      // all good until here
    case 13:
      targetIndex = 278 + (thetaPercent * 5); //10 lights per row
      break;
    case 14:
      targetIndex = 283 + (thetaPercent * 5); // 9 lights per row
      break;
    case 15:
      targetIndex = 288 + (thetaPercent * 4); // 7 lights per row
      break;
    case 16:
      targetIndex = 292 + (thetaPercent * 4); // 7 lights per row 
      break;
    default:
      break; 
  }

  return targetIndex;
}

const int GRAVITY = 150; // the larger, the slower
const int SNOWFLAKE_COUNT = 3;
const unsigned int RANDOM_SEED = 0; 
const double SNOWFLAKE_DRIFT = 60; // the angle from left and right a snowflake should drift
const double SNOWFLAKE_DRIFT_SPEED = 1; // how fast the snowflakes go from left to right

void createSnowflakeAt(double theta, CRGB *leds, double z, CRGB color)
{
  int index = thetaAndZToIndex(theta, z);
  leds[index] = color;
}

void snowing(CRGB *leds, const unsigned int seedOffset)
{
  srand(RANDOM_SEED + seedOffset) // Init rand at our start
  double z_offset = 1.0 - (double(gLoopCounter % GRAVITY) / double(GRAVITY));
  for (int i = 0; i < SNOWFLAKE_COUNT; i++)
  {
    double initial_z = rand() / RAND_MAX; // from 0 to 1
    int theta = (rand() / RAND_MAX) * 360;

    // should fluctuate from + SNOWFLAKE_DRIFT to - SNOWFLAKE_DRIFT 
    theta = theta + (sin(gLoopCounter * SNOWFLAKE_DRIFT_SPEED) * SNOWFLAKE_DRIFT);
    int color = rand() % 5;
    CRGB color = CRGB::Red;
    switch (color)
    {
      case 0:
        color = CRGB::Blue;
        break;
      case 1:
        color = CRGB::White;
        break;
      case 2:
        color = 0x72a3f2; // Cornflower Blue
        break;
      case 3:
        color = 0xa3c0f0; // Tropical Blue
        break;
      case 4:
        color = 0xcedcf5; // Hawkes Blue
        break;
      case 5:
        color = 0xecf3fd; // Alice Blue
        break;
    }
    
    
    createSnowflakeAt(theta, leds, initial_z - z_offset, color);
  }
  
  fadeToBlackBy( leds, NUM_LEDS, 80);
}

void snowing()
{
  snowing(leds1, 1);
  snowing(leds2, 2);
  snowing(leds3, 3);
}

