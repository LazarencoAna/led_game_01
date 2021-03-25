#include <BaseGame.h>

class GameShooter: public BaseGame
{
    coord _userPos;
    coord _shootPos;
 
    byte enemy_matrix[64]; //trebuiesc modificate
    bool visited[4][16];   //trebuiesc modificate

    void randomInit();   //trebuie modificat  generalizat, de dat nr de randuri care va aloca si mem  enemy_matrix si visited
    void deleteEnemy(byte index, byte color);
    void dfs();
    void a();
    bool handleshoot(byte index);

public:
    GameShooter(coord maxCoords, coord minCoords, int gameSpeed);
  
   void Left();
    void Right();
    void Top(){}
    void Bottom(){Shoot();}
    void Shoot();

    void init(); 
    void play();
    byte* getStateList(); 


    coord getShootPos();
    coord getUserPos();

};