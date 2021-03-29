#include <BaseGame.h>

#define NUMBER_OF_LINE 13
#define LINE_SIZE 16 

class GameShooter:  public BaseGame
{
    coord _userPos;
    coord _shootPos;
 
    byte enemy_matrix[NUMBER_OF_LINE * LINE_SIZE]; //trebuiesc modificate
    bool visited[NUMBER_OF_LINE] [ LINE_SIZE]; 
    

    void randomInit();   //trebuie modificat  generalizat, de dat nr de randuri care va aloca si mem  enemy_matrix si visited
    void deleteEnemy(byte index, byte color);
    void a();
    bool handleshoot(byte index);

    void DFS_Iterative (byte src);

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
    std::set<std::pair<std::pair<byte,byte>,byte>> get_StateList(); 


    coord getShootPos();
    coord getUserPos();

};