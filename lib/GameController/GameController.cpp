#include <GameController.h>

GameController::GameController(coord maxCoords, coord minCoords, int gameSpeed)
{
    _maxCoords = maxCoords;
    _minCoords = minCoords;
    _game_speed = gameSpeed;
    _userPos = {0, 0};
    _shootPos = {-1, -1};
};

void GameController::moveUserLeft()
{
    if (_minCoords.x < _userPos.x)
        _userPos.x--;
    Serial.println(_userPos.x);
}       

void GameController::moveUserRight()
{
    if (_maxCoords.x > _userPos.x)
        _userPos.x++;
    Serial.println(_userPos.x);
}

void GameController::shoot()
{
    if(_shootPos.y == -1)
    _shootPos = {_userPos.x, 0};
}
byte getIndex1(byte _x, byte _y)
{
    _x = 15 - _x;
    _y = 15 - _y;
    if (_y % 2 != 0)
    {
        return (15 - _x) + _y * 16;
    }
    return _x + _y * 16;
}
void GameController::play()
{
    if (millis() - _timer > _game_speed)
    {
        _timer = millis();
        if (_shootPos.y > _maxCoords.y)
            _shootPos.y = -1;

        if (_shootPos.y > -1)
            {
                _shootPos.y++;
               if( handleshoot(_shootPos.x+(15-_shootPos.y)*16))
                _shootPos.y = -1;
            }

    }
}


coord GameController::getShootPos()
{
    return _shootPos;
}

coord GameController::getUserPos()
{
    return _userPos;
}


void GameController::init()
{
    randomInit();
}

void GameController::randomInit()
{
    for(int i=0;i<64;i++)
    {
        enemy_matrix[i]=random()%4;
    }
}
byte* GameController::get_enemy_matrix()
{
    return enemy_matrix;
}
bool GameController::handleshoot(byte index)
{
    if (index<64)
    {
        if(enemy_matrix[index]<4)
        {
            delete_enemy(index, enemy_matrix[index]);
            return true;
        }
    }
    return false;
}
void GameController::delete_enemy(byte index, byte color)
{
    if(index>=64)
    return ;
    if(enemy_matrix[index]!=color)
    return ;
    enemy_matrix[index]=4;
    if(index >15)
    delete_enemy(index-16, color);
    if(index%16 >0)
    delete_enemy(index-1, color);
    if(index%16 <15)
    delete_enemy(index+1, color);
    delete_enemy(index+16, color);
}

void GameController::_delete_enemy(byte index)
{

}