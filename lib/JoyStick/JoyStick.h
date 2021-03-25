#include <Arduino.h>
#include <Button.h>

class JoyStick : public Button
{
private:
    int xPosition = 0;
    int yPosition = 0;
    int mapX = 0;
    int mapY = 0;
    uint8_t _VRx;
    uint8_t _VRy;
    unsigned long _joyTimer;

public:
    JoyStick(uint8_t vrx, uint8_t vry, uint8_t sw) : Button(sw){};
    boolean isRight();
    boolean isLeft();
    boolean isTop();
    boolean isBottom();
    void lisen();
};