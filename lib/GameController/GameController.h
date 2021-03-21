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
    byte enemy_matrix[64];
    void randomInit();


public:
    GameController(coord maxCoords, coord minCoords, int gameSpeed);
    void moveUserLeft();
    void moveUserRight();
    void shoot();
    void play();
    void init();
    coord getUserPos();
    coord getShootPos();
    byte* get_enemy_matrix();
};