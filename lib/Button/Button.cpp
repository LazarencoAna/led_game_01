#include <Button.h>

Button::Button(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
    _state = !digitalRead(_pin);
    if (_state && millis() - _timer > debounce)
    {
        _timer = millis();
        return true;
    }
    return false;
}
