#include <DisplayController.h>
#include <GameShooter.h>

DisplayController::DisplayController(){};

void DisplayController::init()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LED);
    FastLED.setBrightness(1);
    delay(200);
}

byte getIndex(byte _x, byte _y)
{
    _x = LINE_SIZE - 1 - _x;
    _y = LINE_SIZE - 1 - _y;
    if (_y % 2 != 0)
    {
        return (LINE_SIZE - 1 - _x) + _y * LINE_SIZE;
    }
    return _x + _y * LINE_SIZE;
}
void DisplayController::Display( std::set<std::pair<std::pair<byte,byte>,byte>> matrix)
{
    if (millis() - _timer > RENDER_SPEED)
    {
        FastLED.clear();
        _timer = millis();
        for (int i = 0; i < NUM_LED; i++)
        {
            leds[i] = 0x000000;
        }
        Serial.println("size");
        Serial.println(matrix.size());
        for (auto i : matrix)
        {
            Serial.println(i.first.first);
            byte j = getIndex(i.first.first, i.first.second);
            switch (i.second)
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
            case 5:
                leds[j] = Green;
                break;
            default:
                leds[j] = 0x000000;
                break;
            }
        }
        

        FastLED.show();
    }
}

void DisplayController::renderGame(coord userPos, coord shootPos, byte *enemy_matrix)
{

    if (millis() - _timer > RENDER_SPEED)
    {
        FastLED.clear();
        _timer = millis();
        int userIndex = getIndex(userPos.x, userPos.y);
        int shootIndex = getIndex(shootPos.x, shootPos.y);
        for (int i = NUM_LED - 1; i >= NUMBER_OF_LINE * LINE_SIZE; i--)
        {
            if (userIndex == i)
            {
                leds[i] = 0x00FF00;
            }
            else if (shootIndex == i)
            {
                leds[i] = 0x00FF00;
            }
            else
            {
                leds[i] = 0x000000;
            }
        }

        for (int i = 0; i < NUMBER_OF_LINE * LINE_SIZE; i++)
        {
            byte j = getIndex(i % LINE_SIZE, LINE_SIZE - 1 - i / LINE_SIZE);
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
                if (shootIndex == j && shootPos.y != -1)
                {
                    leds[j] = 0x00FF00;
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