#include <GameController.h>

GameController::GameController(int index,coord maxCoords, coord minCoords, int gameSpeed)
:myGame(maxCoords,minCoords,gameSpeed)
{
   // myGame= new GameShooter(maxCoords,minCoords,gameSpeed);
};

void GameController::play()
{
   myGame.play();
}

void GameController::init()
{
    myGame.init();
}


void GameController::moveUserLeft()
{
    myGame.Left();
}

void GameController::moveUserRight()
{
    myGame.Right();
}

void GameController::shoot()
{
    myGame.Bottom();
}


coord GameController::getShootPos()
{
    return  myGame.getShootPos();
}

coord GameController::getUserPos()
{
    return myGame.getUserPos();
}

byte *GameController::get_enemy_matrix()
{
    return myGame.getStateList();
}




