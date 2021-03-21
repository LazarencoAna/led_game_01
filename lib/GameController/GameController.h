#include <Coord.h>
#include <Arduino.h>

class GameController
{
private:
    coord _userPos;
    coord _shootPos;
    coord _maxCoords;
    coord _minCoords;
    unsigned long _timer;
    int _game_speed = 200;

public:
    GameController(coord maxCoords, coord minCoords, int gameSpeed);
    void moveUserLeft();
    void moveUserRight();
    void shoot();
    void play();
    coord getUserPos();
    coord getShootPos();
};