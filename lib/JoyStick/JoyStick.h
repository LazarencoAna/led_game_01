#include <Arduino.h>

class JoyStick
{
private:
    uint8_t _VRx;
    uint8_t _VRy;
    uint8_t _SW;
    int xPos = 0;
    int yPos = 0;
    int SW_state = 0;
    int mapX = 0;
    int mapY = 0;
    void init();

public:
    JoyStick(uint8_t vrx, uint8_t vry, uint8_t sw);   
    boolean isRight();
    boolean isLeft();
    boolean isPressed();
};