
void setupHalloween()
{
  baseColor1 = CRGB::DarkOrange;    
  gCurrentPatternNumber = 14;
  FastLED.setBrightness(currentBrightness);
}

void halloween()
{
  // Add a flickering every now and than
  EVERY_N_MILLIS_I(HalloweenFlickerTimer, halloweenFlickerTimer) {
    if ( halloweenFlashState == false ) {
      if ( halloweenFlickerState == false ) {
        // stay black for a short time if not flashing at the moment
        baseColor1 = CRGB::Black;
        halloweenFlickerTimer = random16(50, 100);
        halloweenFlickerState = true;
      } else {
        // return to normal for a longer time
        baseColor1 = CRGB::DarkOrange;
        halloweenFlickerTimer = random16(100, 3000);
        halloweenFlickerState = false;
      }
      FastLED.setBrightness(currentBrightness);
    } else {
      // try again later when not flashing
      halloweenFlickerTimer = random16(500, 1000);
    }
    // Homie.getLogger() << "Flicker: " << halloweenFlickerState << " [" << halloweenFlickerTimer << ", (" << baseColor1.r << ", " << baseColor1.g << ", " << baseColor1.b << ")]" << endl;
    HalloweenFlickerTimer.setPeriod(halloweenFlickerTimer);
  }

  // bright flashing every now and than
  EVERY_N_MILLIS_I(HalloweenFlashTimer, halloweenFlashTimer) {
    if ( halloweenFlickerState == false ) {
      // if not flickering at the moment
      if ( halloweenFlashState == false ) {
        // flash with full brightness and a random pre-defined color
        baseColor1 = halloweenColorArray[random(3)];
        halloweenFlashTimer = random16(200, 400);
        FastLED.setBrightness(255);
        halloweenFlashState = true;
      } else {
        // return to normal for a longer time
        baseColor1 = CRGB::DarkOrange;
        halloweenFlashTimer = random16(3000, 30000);
        FastLED.setBrightness(currentBrightness);
        halloweenFlashState = false;
      }
    } else {
      // try again later when not flickering
      halloweenFlickerTimer = random16(1000, 5000);
    }
    // Homie.getLogger() << "Flash: " << halloweenFlashState << "   [" << halloweenFlashTimer << ", (" << baseColor1.r << ", " << baseColor1.g << ", " << baseColor1.b << ")]" << endl;
    HalloweenFlashTimer.setPeriod(halloweenFlashTimer);
  }

  fill_solid(leds, NUM_LEDS, baseColor1);
}