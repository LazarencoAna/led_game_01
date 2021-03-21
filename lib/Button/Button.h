#include <Arduino.h>

#define debounce 200            // (мс), антидребезг

class Button
{
    private:
        bool _state;
        unsigned long _timer;  
        uint8_t _pin;
    
    public: 
        Button(uint8_t pin);
        bool isPressed();
};