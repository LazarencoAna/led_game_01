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

void GameShooter::a()
{

    for (int i = 0; i < NUMBER_OF_LINE * LINE_SIZE; i++)
    {
        visited[i / LINE_SIZE][i % LINE_SIZE] = false;
    }
    Serial.println(freeMemory());
    for(int i=0;i<LINE_SIZE;i++)
       DFS_Iterative(i);
    for (int i = 0; i < NUMBER_OF_LINE * LINE_SIZE; i++)
        {
            if (!visited[i / LINE_SIZE][i % LINE_SIZE] && enemy_matrix[i] != 4)
            {
                enemy_matrix[i] = 4;
            }
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
 std::set<std::pair<std::pair<byte,byte>,byte>> GameShooter::get_StateList()
{
    std::set<std::pair<std::pair<byte,byte>,byte>> newVector;
    coord _x;
    bool ok=0;
    for (int i = 0; i < NUMBER_OF_LINE * LINE_SIZE; i++)
    {
        if (enemy_matrix[i] != 4){
            _x.x=i % LINE_SIZE;
            _x.y= i / LINE_SIZE;
            newVector.insert(std::make_pair(std::make_pair(i % LINE_SIZE,i / LINE_SIZE),enemy_matrix[i] ));
           
        }
        if(!ok)
        {
            newVector.insert(std::make_pair(std::make_pair(1,1), 3));
            ok=1;
        }
    }
     
    newVector.insert(std::make_pair(std::make_pair(_userPos.x,_userPos.y), 3));
    if (_shootPos.y!=-1)
       newVector.insert(std::make_pair(std::make_pair(_shootPos.x,_shootPos.y), 3));
    return newVector;
}

void GameShooter::DFS_Iterative(byte src)
{
    std::stack<byte> stk;
    visited[0][src] = true;
    stk.push(src);
    byte j = 0;

    while (!stk.empty())
    {
        src = stk.top() % LINE_SIZE;
        j = stk.top() / LINE_SIZE;
        stk.pop();
        visited[0][src] = true;
        if (j < NUMBER_OF_LINE - 1)
            if (!visited[j + 1][src]&&enemy_matrix[(j + 1) * LINE_SIZE + src]!=4)
            {
                visited[j + 1][src] = true;
                stk.push((j + 1) * LINE_SIZE + src);
            }
        if (src < LINE_SIZE - 1 )
            if (!visited[j][src + 1]&&enemy_matrix[j * LINE_SIZE + src + 1]!=4)
            {
                visited[j][src + 1] = true;
                stk.push(j * LINE_SIZE + src + 1);
            }
        if (j > 0)
            if (!visited[j - 1][src]&&enemy_matrix[(j - 1) * LINE_SIZE + src]!=4)
            {
                visited[j - 1][src] = true;
                stk.push((j - 1) * LINE_SIZE + src);
            }
        if (src > 0)
            if (!visited[j][src - 1]&&enemy_matrix[j * LINE_SIZE + src - 1]!=4)
            {
                visited[j][src - 1] = true;
                stk.push(j * LINE_SIZE + src - 1);
            }

    }
}