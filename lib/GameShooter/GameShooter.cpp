#include <GameShooter.h>
#include <MemoryFree.h>

GameShooter::GameShooter(coord maxCoords, coord minCoords, int gameSpeed) : BaseGame(maxCoords, minCoords, gameSpeed)
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
    for (int i = 0; i < NUMBER_OF_LINE * LINE_SIZE; i++)
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
    if (index >= NUMBER_OF_LINE * LINE_SIZE)
        return;
    if (enemy_matrix[index] != color)
        return;
    enemy_matrix[index] = 4;
    if (index > LINE_SIZE - 1)
        deleteEnemy(index - LINE_SIZE, color);
    if (index % LINE_SIZE > 0)
        deleteEnemy(index - 1, color);
    if (index % LINE_SIZE < LINE_SIZE - 1)
        deleteEnemy(index + 1, color);
    deleteEnemy(index + LINE_SIZE, color);
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
            if (handleshoot(_shootPos.x + (LINE_SIZE - 1 - _shootPos.y) * LINE_SIZE))
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
    return r >= 0 && r < NUMBER_OF_LINE && c >= 0 && c < LINE_SIZE;
}

bool GameShooter::dfs()
{
    bool ok = 1;
    bool ok2 = 0;
    for (int i = 0; i < LINE_SIZE; i++)
    {
        if (enemy_matrix[i] != 4)
            visited[0][i] = true;
    }
    while (ok)
    {
        ok = 0;
        for (int i = 0; i < LINE_SIZE; i++)
            for (int j = 1; j < NUMBER_OF_LINE; j++)
            {
                if (enemy_matrix[i + j * LINE_SIZE] != 4 && visited[j - 1][i] && !visited[j][i])
                {
                    visited[j][i] = true;
                    ok = 1;
                }
            }
        for (int i = 0; i < LINE_SIZE; i++)
            for (int j = 1; j < NUMBER_OF_LINE; j++)
            {
                if (enemy_matrix[i + j * LINE_SIZE] != 4 && !visited[j][i])
                {
                    if (i > 0)
                    {

                        if (visited[j][i - 1])
                        {
                            visited[j][i] = true;
                            ok = 1;
                        }
                    }
                    if (i < LINE_SIZE - 1)
                    {

                        if (visited[j][i + 1])
                        {
                            visited[j][i] = true;
                            ok = 1;
                        }
                    }
                }
            }
        for (int i = 0; i < LINE_SIZE; i++)
            for (int j = 1; j < NUMBER_OF_LINE - 1; j++)
            {
                if (enemy_matrix[i + j * LINE_SIZE] != 4 && visited[j + 1][i] && !visited[j][i])
                {
                    visited[j][i] = true;
                    ok = 1;
                }
            }
        if (ok)
            ok2 = true;
    }
    if (!ok2)
    {
        return false;
    }
    return true;
}

void GameShooter::a()
{

    for (int i = 0; i < NUMBER_OF_LINE * LINE_SIZE; i++)
    {
        visited[i / LINE_SIZE][i % LINE_SIZE] = false;
    }
    Serial.println(freeMemory());
    if (dfs())

        for (int i = 0; i < NUMBER_OF_LINE * LINE_SIZE; i++)
        {
            if (!visited[i / LINE_SIZE][i % LINE_SIZE] && enemy_matrix[i] != 4)
            {
                enemy_matrix[i] = 4;
            }
        }
    else
    {
       // delete[] visited;
        Serial.println(freeMemory());
        Serial.println("da");

    }
}

bool GameShooter::handleshoot(byte index)
{
    if (index < NUMBER_OF_LINE * LINE_SIZE)
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