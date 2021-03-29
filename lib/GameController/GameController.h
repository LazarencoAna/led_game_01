#include <Coord.h>
#include <Arduino.h>
#include <GameShooter.h>

class GameController
{
private:
    BaseGame*  myGame;
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
    std::set<std::pair<std::pair<byte,byte>,byte>> get_enemy_matrix();
    byte* get_enemy_matri()
    {
        return myGame->getStateList();
    }

};