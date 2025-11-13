#include <vector>
#include <iostream>
using namespace std;
class Player;
class Maze;
bool wallIsValid(vector<vector<char>>& mazeMap, int x, int y, bool vertical);
string convertMove(string move);
float calcDist(int distX,int distY);
void resetMaze(vector<vector<char>>& mazeMap);
void mazeEndCheck(vector<vector<char>>& mazeMap,Player *player);