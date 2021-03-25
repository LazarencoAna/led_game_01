#include <GameShooter.h>

GameShooter::GameShooter(coord maxCoords, coord minCoords, int gameSpeed) :BaseGame(maxCoords, minCoords, gameSpeed)
{
    _userPos = {0, 0};
    _shootPos = {-1, -1};
};

void GameShooter::Left()
{
    if (_minCoords.x < _userPos.x)
        _userPos.x--;
}

void GameShooter::Right()
{
    if (_maxCoords.x > _userPos.x)
        _userPos.x++;
}

void GameShooter::Shoot()
{
    if (_shootPos.y == -1)
        _shootPos = {_userPos.x, 0};
}

void GameShooter::init()
{
    randomInit();
}

void GameShooter::randomInit()
{
    for (int i = 0; i < 64; i++)
    {
        enemy_matrix[i] = random() % 4;
    }
}
byte *GameShooter::getStateList()
{
    return enemy_matrix;
}

void GameShooter::deleteEnemy(byte index, byte color)
{
    if (index >= 64)
        return;
    if (enemy_matrix[index] != color)
        return;
    enemy_matrix[index] = 4;
    if (index > 15)
        deleteEnemy(index - 16, color);
    if (index % 16 > 0)
        deleteEnemy(index - 1, color);
    if (index % 16 < 15)
        deleteEnemy(index + 1, color);
    deleteEnemy(index + 16, color);
}

void GameShooter::play()
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




boolean ok(int r, int c)
{
    return r >= 0 && r < 4 && c >= 0 && c < 16;
}

void GameShooter::dfs()
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
        for (int i = 0; i < 16; i++)
            for (int j = 1; j < 3; j++)
            {
                if (enemy_matrix[i + j * 16] != 4 && visited[j +1][i]&&!visited[j][i])
                   { visited[j][i] = true;
                ok = 1;}
            }
    }
}

void GameShooter::a()
{

    for (int i = 0; i < 64; i++)
    {
            visited[i / 16][i % 16] = false;
    }
    dfs(); 

    for (int i = 0; i < 64; i++)
    {
        if (!visited[i / 16][i % 16] && enemy_matrix[i] != 4)
        {
            enemy_matrix[i] = 4;
        }
    }
}

bool GameShooter::handleshoot(byte index)
{
    if (index < 64)
    {
        if (enemy_matrix[index] != 4)
        {
            deleteEnemy(index, enemy_matrix[index]);

            return true;
        }
    }
    return false;
}

coord GameShooter::getShootPos()
{
    return _shootPos;
}

coord GameShooter::getUserPos()
{
    return _userPos;
}