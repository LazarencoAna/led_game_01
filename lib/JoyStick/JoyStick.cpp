#include <JoyStick.h>

JoyStick::JoyStick(uint8_t vrx, uint8_t vry, uint8_t sw)
{
    _VRx = vrx;
    _VRy = vry;
    _SW = sw;

    pinMode(_VRx, INPUT);
    pinMode(_VRy, INPUT);
    pinMode(_SW, INPUT_PULLUP);
};