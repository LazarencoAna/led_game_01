#include <GameController.h>
#include <MemoryFree.h>

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
    if (_shootPos.y == -1)
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
            if (handleshoot(_shootPos.x + (15 - _shootPos.y) * 16))
            {

                _shootPos.y = -1;
                a();
            }
            Serial.println(_shootPos.y);
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
    for (int i = 0; i < 64; i++)
    {
        enemy_matrix[i] = random() % 4;
    }
}
byte *GameController::get_enemy_matrix()
{
    return enemy_matrix;
}
void GameController::delete_enemy(byte index, byte color)
{
    if (index >= 64)
        return;
    if (enemy_matrix[index] != color)
        return;
    enemy_matrix[index] = 4;
    if (index > 15)
        delete_enemy(index - 16, color);
    if (index % 16 > 0)
        delete_enemy(index - 1, color);
    if (index % 16 < 15)
        delete_enemy(index + 1, color);
    delete_enemy(index + 16, color);
}

boolean ok(int r, int c)
{
    return r >= 0 && r < 4 && c >= 0 && c < 16;
}

void GameController::dfs()
{
    bool ok = 1;
    for (int i = 0; i < 16; i++)
    {
        if (enemy_matrix[i] != 4)
            visited[0][i] = true;
    }
    while (ok)
    {
        ok = 0;
        Serial.println(freeMemory());
        for (int i = 0; i < 16; i++)
            for (int j = 1; j < 4; j++)
            {
                if (enemy_matrix[i + j * 16] != 4 && visited[j - 1][i]&&!visited[j][i])
                    {visited[j][i] = true;
                ok = 1;}
            }
        for (int i = 0; i < 16; i++)
            for (int j = 1; j < 4; j++)
            {
                if (enemy_matrix[i + j * 16] != 4&&!visited[j][i])
                   {
                       if (i > 0)
                    {

                        if (visited[j][i - 1])
                          {  visited[j][i] = true;
                        ok = 1;}
                    }
                     if (i  <15)
                    {

                        if (visited[j][i + 1])
                           { visited[j][i] = true;
                        ok = 1;}
                    }
                   } 
            }
        Serial.println(freeMemory());
        for (int i = 0; i < 16; i++)
            for (int j = 1; j < 3; j++)
            {
                if (enemy_matrix[i + j * 16] != 4 && visited[j +1][i]&&!visited[j][i])
                   { visited[j][i] = true;
                ok = 1;}
            }
    }
}

void GameController::a()
{

    for (int i = 0; i < 64; i++)
    {
    
            visited[i / 16][i % 16] = false;
    }

    Serial.println("dfs");
    Serial.println(freeMemory());
 
     dfs(); // get the contiguous count
     Serial.println("dfs2");

    for (int i = 0; i < 64; i++)
    {
        if (!visited[i / 16][i % 16] && enemy_matrix[i] != 4)
        {
            enemy_matrix[i] = 4;
        }
    }
}

bool GameController::handleshoot(byte index)
{
    if (index < 64)
    {
        if (enemy_matrix[index] != 4)
        {
            delete_enemy(index, enemy_matrix[index]);

            return true;
        }
    }
    return false;
}