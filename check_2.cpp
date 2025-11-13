#include"function_dec.h"
#include <string>
#include <cmath>



/*
    1. This Player object needs ints for its position 
    2. a symbol to identify the player with

    All these variables should be private to avoid tampering

    3. a function to move the player
        A. You need to know where you are and where you will end up
        B. You need to edit the position of the player
        C. The new position can not be on a wall
        D. edit the moves vector if and only if the player moves

    4. for each of the private variables we need a get function to access them
*/
class Player{
    private:
        int x;
        int y;
        vector<string> moves;
        char playerSymbol;
    public:
        Player(int x,int y, char symb) : x(x), y(y), playerSymbol(symb){}
       
        void move (vector<vector<char>>& mazeMap,string move){
            int tempX = x;
            int tempY = y;

            if (move== "u" && y>0){
                y--;   
            }
            else if (move== "d" && y<mazeMap.size()-1){
                y++;
            }
            else if (move== "r" && x<mazeMap.at(0).size()-1){
                x++;
            }
            else if (move== "l" &&x>0){
                x--;
            }
            else{
                cout << "Invalid Input" << endl;
                return;
            }
            if (mazeMap[y][x]=='*' && x!= tempX  || y!= tempY ){
              
                mazeMap[y][x]=playerSymbol;
                mazeMap[tempY][tempX]= '*';
                
            }
            else{
                x=tempX;
                y= tempY;
                cout << "I Can't go there!" << endl;
            }
        }
        char getPlayerSymbol(){
            return playerSymbol;
        }
        vector<string> getMoves(){
            return moves;
        }
        
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
};


/*  
    1. This class needs a height, a width and its map,
    2. Now we make constructor that also generates the map with a 2-Dimensional vector of proper size 
    3. A function that places the player on the specifed spot
    4. A first map should be made to show that the player's position setting works
    5. A second  map should be made this map should be 4*4 or 5*5 if you want.
    6. A third map should also be generated where it is specifically 7 wide * 2 high  
*/
class Maze{
    private: 
        int height;
        int width;
        vector<vector<char>> mazeMap; 
    public: 
    Maze(){}
    Maze(int len, int wid, char emptySymbol): height(len), width(wid) {
        for (int i  = 0; i < len; i++){
            vector<char> temp;
            for (int j = 0; j < wid; j++){
                temp.push_back(emptySymbol);
            }
            mazeMap.push_back(temp);
        }
    }
   ~Maze(){}
    vector<vector<char>>& getMazeState(){
        return mazeMap;
    }
    void showMaze();
    void placeWall( bool vertical, int x, int y);

    Player placePlayer(char symbol, int posX, int posY){
        if (posX < width && posY < height){
            mazeMap[posY][posX] = symbol;
            Player p(posX,posY,symbol);
            return p;
        }
        mazeMap[posY][posX] = symbol;
        cout << "Player placement invalid placed at 0,0" << endl;
        Player p(0,0,symbol);
        return p;
    }
};
/*
    1. Find the position of the other half of the wall
    2. Then update then map with both new walls
*/
void Maze::placeWall( bool vertical, int x, int y){
        int otherPos = vertical ? y+1 : x+1; // ternary operator  bool ? if true: if false
        if (vertical){
            mazeMap[y][x]= '|';
            mazeMap[otherPos][x] = '|';   
        }else{
            mazeMap[y][x] = '-';
            mazeMap[y][otherPos] = '-';
        }
       
    } 
    
/*
    How deep of a nested loop would be needed in order to see a single position on the map?
    We want this to display just like the vector in the main function
*/
void Maze::showMaze(){
    for(vector line : mazeMap){
            for (char space : line){
                cout << space << "  ";
            }
            cout << endl;
        }
        cout << endl << endl;
        
} 

/*
    This function checks if a wall can be placed with the given parameters
    Consider these things; Can it be on the player? Can it intersect another wall? 
    Can it be outside of the bounds of the map?
    if any of these things happen what should be returned?
*/
bool wallIsValid(vector<vector<char>>& mazeMap, int x, int y, bool vertical){
    int otherWallX=0;
    int otherWallY=0;
    if (vertical){
        otherWallX=x;
        otherWallY=y+1;
    }else{
        otherWallX=x+1;
        otherWallY=y;
    }
    if (x< 0 || y< 0){
        return false;
    }
    if (x > mazeMap.at(0).size()-1 || otherWallX > mazeMap.at(0).size()-1 
    || y > mazeMap.size()-1 || otherWallY > mazeMap.size()-1){
        return false;
    }
    if (  mazeMap[y][x] != '*' || mazeMap[otherWallX][otherWallY]!= '*'){
        return false;
    }
    return true;
}

/*
Our move function has a problem if given random capitals at any point in the input 
the function breaks (ie. UP or Up or uP)
how can we fix this for any given input?
*/ 
string convertMove(string move){
    for (char& c : move){
        c=tolower(c);
    } 
    return move;
}

   // You may need to include something in order to get the functions you need
float calcDist(int distX,int distY){
    //TODO: Complete this function!
}

 /*
    Think about how to get the total distance from any two points on a 2-Dimensional grid (think triangles)
    and what can you do to get the amount of moves made?
*/
void calcMazeStats(vector<string> moves){
    //TODO: Complete this function!
}
    
/*
    1. Get the symbol for the player
    2. Find where the player is on the map
    3. compare player position to the end of the maze
    4. calculate the stats
*/
void mazeEndCheck(vector<vector<char>>& mazeMap,Player *player){
    //TODO: Complete this function!
}

/*
    This should loop through each string in the map and change it back to '*'
*/
void resetMaze(vector<vector<char>>& mazeMap){
   //TODO: Bonus function!
}
 

bool setupMaze(string wallNum, Maze* maze){
    int x;
    int y;
    vector<vector<char>> mazeMap= maze->getMazeState();
    bool vert;
    string dir;
    while (true) {
        cout << "Wall " << wallNum << " x coordinate: ";
        if (cin >> x) break;
        cout << "Invalid input. Please enter an integer.\n";
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    while (true) {
        cout << "Wall " << wallNum << " y coordinate: ";
        if (cin >> y) break; 
        cout << "Invalid input. Please enter an integer.\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "Wall "<< wallNum<< " orientation (vertical {v} or horizontal {h}):";
    cin >> dir;
    if (dir == "vertical" || dir== "v"){
        vert=true;
    }    else if (dir == "horizontal" || dir== "h"){
        vert=false;
    }else{
        cout<< "Invalid direction! Restarting..." <<endl;
        return false;
    }
    cout << "Checking validity of wall " << wallNum << "..."<< endl;

    try{
        if(wallIsValid(mazeMap, x,y,vert)){
            maze->placeWall(vert,x,y);
            return true;
        }
    }catch(invalid_argument& e){
        cout << "ERROR Expected input order: int, int, string/char" << endl;
    }
    return false;
}

Maze selectMaze( char& selectedLevel, Player &player){
    Maze maze1(5,5,'*');
    Maze maze2(2,7,'*');
    Maze testMaze(2,2,'*');
    Maze currMaze;
    while (selectedLevel != '0' && selectedLevel != '1' && selectedLevel != '2' && selectedLevel != 'Q'){
        cout << "Choose 0 for the testing maze" << endl
             << "Choose 1 for maze one" << endl;
        cout << "Choose 2 for maze two" << endl
             << "Choose q/Q at anytime to go back/quit" << endl;
        cin >> selectedLevel;
        switch (selectedLevel){
        // specifically for part 1, can be used later
        case '0':
            currMaze = testMaze;
            cout << "Testing maze selected" << endl;
            player = currMaze.placePlayer('P', 0, 0);
            currMaze.placeWall(true, 1, 0);
            break;
        case '1':
            currMaze = maze1;
            cout << "Maze " << selectedLevel << " Selected" << endl;
            player = currMaze.placePlayer('P', 0, 0);
            cout << "wall validation check 1: " <<wallIsValid(currMaze.getMazeState(), -1,-1,true) << endl;//false, checks in bounds condition (less than)
            cout << "wall validation check 2: " <<wallIsValid(currMaze.getMazeState(), player.getX(),player.getY(),false) << endl; // false, check if not on player condition was made
            cout << "wall validation check 3: " <<wallIsValid(currMaze.getMazeState(), 6,10,false) << endl; // false, checks in bounds conditions (greater than)
            cout << "wall validation check 4: " <<wallIsValid(currMaze.getMazeState(), 1,0,true) << endl; //  true
            currMaze.placeWall(true, 1, 0);
            cout << "wall validation check 5: " <<wallIsValid(currMaze.getMazeState(), 1,0,true) << endl; // false, checks wall on wall condition
            currMaze.placeWall(false, 0, 3);
            currMaze.placeWall(true, 3, 1);
            currMaze.placeWall(true, 2, 3);
            break;
        case '2':
            currMaze = maze2;
            cout << "Maze " << selectedLevel << " Selected" << endl;
            player = currMaze.placePlayer('P', 0, 0);
            break;
        case 'Q':
            cout << "Bye Bye!" << endl;
            break;
        default:
            cout << "Invalid Input" << endl
                 << endl;
            break;
        }
    }
    return currMaze;
}

void setupInit(Maze currMaze){

    cout << "Make this maze take the maximum amount of moves," << endl;
    cout << "while still being completable." << endl;
    cout << "If the wall is invalid for the maze, it will repeat" << endl;
    do{
        if (setupMaze("one", &currMaze)){
            break;
        }
    } while (true);

    cout << "Wall one Placed" << endl;
    currMaze.showMaze();
    do{
        if (setupMaze("two", &currMaze)){
            break;
        }
    } while (true);

    cout << "Wall two Placed" << endl;
    currMaze.showMaze();
    cout << "Setup finished" << endl;
}

void playMaze(char selectedLevel, bool& setup, Maze* currMaze, Player *player){
    string moveInput;
    
    while (currMaze->getMazeState()[currMaze->getMazeState().size() - 1][currMaze->getMazeState().at(0).size() - 1] != player->getPlayerSymbol()){
        if (selectedLevel == '2' && !setup){
            setupInit(*currMaze);
            setup = true;
        }
        cout << "I want to move... ";
        cin >> moveInput;
        if (toupper(moveInput.at(0)) == 'Q'){
            break;
        }
        moveInput = convertMove(moveInput);
        player->move(currMaze->getMazeState(), moveInput);
        currMaze->showMaze();
    }
}

int main(){
   
    char selectedLevel;

    do{
        Player *player= new Player(0,0,'P');
        Maze currMaze = selectMaze(selectedLevel, *player);

        if (toupper(selectedLevel) == 'Q'){
            break;
        }

        currMaze.getMazeState()[player->getX()][player->getY()] = player->getPlayerSymbol();
        
        bool setup = false;
        currMaze.showMaze();
        playMaze(selectedLevel,setup,&currMaze,player);
        currMaze.showMaze();
        mazeEndCheck(currMaze.getMazeState(), player);
       // resetMaze(mazeMap);
        selectedLevel = '~';
        player->~Player();
    }while(selectedLevel != 'Q');
}