#include <Arduino.h>
#include <Coord.h>
#include "FastLED.h"

#define RENDER_SPEED 100
#define NUM_LED 256
#define LED_PIN 5

class DisplayController
{
private:
    unsigned long _timer;
    uint8_t _brightness;
    CRGB leds[NUM_LED];

public:
    DisplayController();
    void init();
    void renderGame(coord userPos, coord shootPos);
};