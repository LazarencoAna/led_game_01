#include <Coord.h>
#include <ArduinoSTL.h>

class BaseGame
{
protected:
    coord _maxCoords;
    coord _minCoords;
    unsigned long _timer;
    int _game_speed = 200;

public:
    BaseGame(coord maxCoords, coord minCoords, int gameSpeed)
    {
        _maxCoords = maxCoords;
        _minCoords = minCoords;
        _game_speed = gameSpeed;
    }
    virtual void Left(){}
    virtual void Right(){}
    virtual void Top(){}
    virtual void Bottom(){}
    virtual void init(){}
    virtual void play(){}
    virtual byte *getStateList(){return nullptr;}
    virtual std::set<std::pair<std::pair<byte,byte>,byte>> get_StateList() {    }


    //sterge 
     virtual coord getShootPos(){return {0,0};}
     virtual coord getUserPos(){return {0,0};}
};