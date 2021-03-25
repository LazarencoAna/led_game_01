#include <DisplayController.h>

DisplayController::DisplayController(){};

void DisplayController::init()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LED);
    FastLED.setBrightness(1);
    delay(200);
}

byte getIndex(byte _x, byte _y)
{
    _x = 15 - _x;
    _y = 15 - _y;
    if (_y % 2 != 0)
    {
        return (15 - _x) + _y * 16;
    }
    return _x + _y * 16;
}

void DisplayController::renderGame(coord userPos, coord shootPos, byte *enemy_matrix)
{

    if (millis() - _timer > RENDER_SPEED)
    {
        FastLED.clear();
        _timer = millis();

        int userIndex = getIndex(userPos.x, userPos.y);
        int shootIndex = getIndex(shootPos.x, shootPos.y);
        for (int i = NUM_LED - 1; i >= 64; i--)
        {
            if (userIndex == i)
            {
                leds[i] = 0x00FF00;
            }else
            if (shootIndex == i)
            {
                leds[i] = 0x00FF00;
            }else 
            {
                leds[i] = 0x000000;
            }
        }

        for (int i = 0; i < 64; i++)
        {
            byte j = getIndex(i % 16, 15 - i / 16);
            switch (enemy_matrix[i])
            {
            case 0:
                leds[j] = Red;
                break;
            case 1:
                leds[j] = Blue;
                break;
            case 2:
                leds[j] = Yellow;
                break;
            case 3:
                leds[j] = Pink;
                break;
            case 4:
                if (shootIndex == i && shootPos.y != -1)
                {
                    leds[i] = 0x00FF00;
                }
                break;
            default:
                leds[i] = 0x000000;
                break;
            }
        }

        FastLED.show();
    }
}