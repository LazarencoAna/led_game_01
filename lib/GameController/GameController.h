#include <Coord.h>
#include <Arduino.h>
#include <GameShooter.h>

class GameController
{
private:
    GameShooter  myGame;
public:
    GameController(int index,coord maxCoords, coord minCoords, int gameSpeed);// modificam 
    void moveUserLeft();
    void moveUserRight();
    void shoot();
    void play();
    void init(); 

    bool handleshoot(byte index);

    coord getUserPos();
    coord getShootPos();
    byte* get_enemy_matrix();

};