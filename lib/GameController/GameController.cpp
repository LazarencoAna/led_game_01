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

void GameController::play()
{
    if (millis() - _timer > _game_speed)
    {
        _timer = millis();
        if (_shootPos.y > _maxCoords.y)
            _shootPos.y = -1;

        if (_shootPos.y > -1)
            _shootPos.y++;

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