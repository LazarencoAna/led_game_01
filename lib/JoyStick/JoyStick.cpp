#include <JoyStick.h>

JoyStick::JoyStick(uint8_t vrx, uint8_t vry, uint8_t sw) : Button(sw)
{
    _VRx = vrx;
    _VRy = vry;
    pinMode(vrx, INPUT);
    pinMode(vry, INPUT);
};

void JoyStick::lisen()
{
    xPosition = analogRead(_VRx);
    yPosition = analogRead(_VRy);
    mapX = map(xPosition, 0, 1023, -10, 10);
    mapY = map(yPosition, 0, 1023, -10, 10);
}

boolean JoyStick::isTop()
{
    if (mapY > 2 && millis() - _joyTimer > debounce)
    {
        _joyTimer = millis();
        return true;
    }
    return false;
}

boolean JoyStick::isBottom()
{
    if (mapY < -2 && millis() - _joyTimer > debounce)
    {
        _joyTimer = millis();
        return true;
    }
    return false;
}

boolean JoyStick::isRight()
{
    if (mapX < -2 && millis() - _joyTimer > debounce)
    {
        _joyTimer = millis();
        return true;
    }
    return false;
}

boolean JoyStick::isLeft()
{
    if ((mapX > 2) && (millis() - _joyTimer) > debounce)
    {
            Serial.println(mapX);
    Serial.println(_joyTimer);
        _joyTimer = millis();
        return true;
    }
    return false;
}
