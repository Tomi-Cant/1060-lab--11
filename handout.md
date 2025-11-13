# CSCI 1060U - Laboratory #11

In this lab we will delve further into our study of object-oriented programming (OOP) with classes. Like a structure, a class is a blueprint for creating objects that define their properties, but it also defines object behavior. Classes are a fundamental concept of OOP and provide a way to organize and encapsulate related data and functions into a single unit.

A class serves as a template or a user-defined data type that describes both the properties (data members) and actions (member functions) that objects of that class can have. The data members represent the state or attributes of the objects, while the member functions define their behavior and operations.

Here's an example of a simple class in C++:

``` C++

class Person {
public:
    // Data members
    string name;
    int age;

    // Member function
    void introduce() {
        cout << "My name is " << name << " and I am " << age << " years old." << endl;
    }
};

```

In the above example, the Person class has two data members: name and age. It also has a member function called introduce() which prints out the name and age of a person. Once a class is defined, you can create objects (instances) of that class using the class name the same way you did for structures:

``` C++
Person person1;  // Creating an object of the Person class
person1.name = "John";
person1.age = 25;
person1.introduce();  // Output: My name is John and I am 25 years old.
```

In this lab we will also be making use of a vector. A vector is a dynamic array-like container provided by the Standard Template Library (STL). It is one of the most commonly used containers in C++ due to its flexibility and convenience.

A vector allows you to store and manipulate a collection of elements of the same type. Unlike static arrays, vector automatically manages the memory allocation and deallocation for its elements, allowing it to resize dynamically as needed. This means we won't need to do much work to implement one for this lab, but we do need to understand how it works. Here is a brief example of what this might look like for a Person class:

``` C++
#include <vector>
#include <iostream>
using namespace std;
int main() {
    vector<string> fruits;

    fruits.push_back("Apple");
    fruits.push_back("Banana");
    fruits.push_back("Orange");

    for (string fruit : fruits) {
        cout << fruit << endl;
    }

    return 0;
}

```

In this example, we create a vector called fruits to store strings. We add three elements to the vector using the push_back() function. Each element represents a fruit: "Apple", "Banana", and "Orange". We then use a range-based for loop to iterate over the elements of the vector and print them. If you are taking CSCI 1030 alongside this course, you are probably familiar with the python syntax:

```python
for item in lst:
    #do stuff
```

Up until this point in the course, we have not had a 'list' structure that allows us to use the same
format. With vectors, we can now do exactly that using a for loop, grabbing each element of the vector one at a time.

## Getting Started

In this lab, we'll be using a class to represent a Maze using height width and a 2D vector for a map and a class called Player, including the starting position, the moves it makes throughout the game and a symbol that will represent it. In order to store all the moves made and maze maps in our program, we'll use a vector rather than an array for easier dynamic updating.

The lab starts you off with two nearly empty classes but we are going to tackle the Maze class first. In the maze class we have to initialize some member variables namely being height, width, and that 2D vector mentioned earlier called mazeMap for a 2D vector they are declared as such `vector<vector<var_type>>`.

For this class we want to have two constructors one that contains the height and the width of the maze itself and also a char to set what an empty space looks like, on top of that this constructor gets some code inside its definition too. This constructor needs to build the map to the given width and length with the empty space symbol. Recall the vector for loop from earlier, how would we go into the second layer of the vector? (think about using temporary variables here).

Heres another example for classes if you get stuck:

```C++
#include <iostream>
#include <string>
using namespace std;
class Person {
public:
    string name;
    int age;

    // Constructor
    Person(string newName, int newAge) {
        name = newName;
        age = newAge;
        cout << "Person object created: " << name << ", " << age << " years old." << endl;
    }
};

int main() {
    // Create a person object using the constructor
    string name = "John Doe"
    Person person(name, 25);
    return 0;
}
```

_Note how the constructor name is the same as the class name, this is necessary._

The second necessary constructor is a completely empty one that acts a way to initialize a dummy object to act as one of the real mazes later on. After making our constructors before we leave the class for the time being we need to put a accessor here

`vector<vector<char>>& getMazeState(){` this should be a simple return of the maze map so it can be seen outside of the Maze class.

Moving on to the skeleton for a Player class, which we will work on first. First, we need to define our move function

`void move(vector<vector<char>>& mazeMap,string move){`.

Starting with the move function, we need to track:

1. The position of the player before
2. The position of the player after
3. Where the player wants to move
4. If the move is valid (in bounds)

Some things to think about; how do you check if it is at the edge of the map? what ways can we track its old and new position? and if there was something else already on the space the player is going to what should happen?

We also need to define some accessors for the Player class this includes `char getPlayerSymbol(){`, `vector<string> getMoves(){`, `int getX(){` and `int getY(){`.

with our two classes sufficiently filled for now we need to make a few changes to the rest of the file. We'll start off with defining the `void Maze::showMaze(){` and `string convertMove(string move){` functions.

For `void Maze::showMaze(){`, we will do things in a similar way as in the creation of the maze map, make sure it is spaced correctly, keep in mind since `showMaze` is part of the maze class it can access its private variables. For a 3x3 grid it should look like this (given your empty space is '*'):

```
*   *   *
*   *   *
*   *   *
```

It is also a good idea to have a little bit of spacing after showing the maze to reduce the cluttered feel.

For the `string convertMove(string move){` function, we want to avoid issues with having inconsistent capitals inside our inputs so we want to standardize them before reading and preforming actions with them. Here's a hint,

``` c++
for (int n : iterable_name){
    //do stuff
}
```

isn't the only variable type that can be iterated through in this way.

To test that we've done things correctly, create 3 mazes in the top of the selectMaze function using your new constructor. These mazes should be as follows:

1. `testMaze` a 2*2 maze
2. `maze1` a 5*5 maze
3. `maze2` a 7 wide * 2 high maze

Finally run the code and select 0 for the test maze for now. You should be able to move and on start it should look something like this:

```
P   *
*   *
```

**_Show your TA your work, then switch your driver and navigator roles before
moving on._**

## Making obstacles

At this point we can make mazes and move our player around the maze, but these aren't really mazes they're just big open spaces. This is where the functions `placeWall` and `wallIsValid` come into play.
Now technically the wallIsValid is not necessary yet but it makes sense to put it here so we can really get a feel for how the walls should work before moving on.

For `void Maze::placeWall(bool vertical, int x, int y){` we need to understand what walls should do they should:

1. only be on spaces with the empty symbol
2. have two distinct versions; horizontal and vertical
3. and should be 2 spaces long adding 1 to its position in that direction (eg. is vertical (y,x) and (newY, x)). **Note that it is y then x this is because of the way the vector is accessed and formatted.**

With these 3 rules in mind we need to simply get the walls to be placed inside the map there's no need to worry about where they are being placed as that has been taken care of for you for what you will need it for.
For the other function  

`bool wallIsValid(vector<vector<char>>& mazeMap, int x, int y, bool vertical){`

it's a bit trickier since there are a lot of things to consider when determining whether or not it is valid like: Can it be on the player? Can it intersect another wall?
Can it be outside of the bounds of the map? If any of these things happen what should be returned?

Upon finishing this function, run the code yet again and select 1 or 0 to see the wall functions in action they should look something like:

```
test maze
P   |
*   |
```

```
maze 1
P  |  *  *  *
*  |  *  |  *
*  *  *  |  *
-  -  |  *  *
*  *  |  *  *  
```

We should dispose of players after the level is completed we can do this by calling a class destructor on the player we are working with. In the bottom of the main do/while loop we need to call `player.~Player();`
In order to test that you wall validation I made it easier to check for the basics with 5 tests which should print:

``` C++
wall validation check 1: 0 
wall validation check 2: 0
wall validation check 3: 0
wall validation check 4: 1
wall validation check 5: 0
```

**_Show your TA your work, then switch your driver and navigator roles before
moving on._**

## Vector Mutation

At the current moment our moves aren't being tracked so we have no idea where we started and what steps took us there. This is where the move vector in the player class comes into play every time we move the move will be given to the vector to track the moves made. To do this we will use the method push_back to add a new element to a vector:

``` C++
vector<string> fruits;
fruits.push_back("Apple");
fruits.push_back("Banana");
```

Although a vector uses dynamic memory, it does not require us to write any code to resize it or keep track of its size. Every time the push_back method is called, space is allocated to fit the new element which is stored at the end of the vector. You can still access elements of a vector the same way you do with an array - in the code above, fruits[1] is "Banana". we can also use fruits.at(1) which will tell us if it is out of bounds of the vector.

Now we'll finish up the missing code. In the move function, there is one line that needs to be added to it when the player successfully moves which is a push back to the moves vector.
Adding to the vector is cool but what's cooler is actually doing something with the vectors. In order to do that, we are going to tackle the `mazeEndCheck`, `calcMazeStats` and `calcDist` functions.

Starting with mazeEndCheck this doesn't directly interact with the vector but does start off a chain of function calls later.This function needs to check if the player is in the right-bottommost spot and print whether or not the maze was completed, with the bottom right being considered completed. Then we need calculate the stats of the maze run by calling calcMazeStats and filling out its parameters.

Working down the chain, the next function is the calcMazeStats. This function is responsible for 2 things; getting the total distance traveled and the total moves made throughout the run. We are going to loop through the vector and then tracking the absolute value of distance traveled. After tracking the distance traveled we now need to calculate the spaces moved down to the decimal. Where? In calcDist(). How? Triangles. Triangles squared. (Also get rid of the return 0.0 when you implement it).

To test your functions, select maze 1 and then get to the right bottom corner then move the starting position and test again to prove that it is truly calculating distance moved by player.

**_Show your TA your work, then switch your driver and navigator roles before moving on._**

## Adding a Collectible

This is going to be the simplest in concept but could be much more difficult in practice. You may notice that all the functions and classes are filled out, but that doesn't mean that we are done, reason being that we are now going to edit these functions and classes.

1. In the player class we now need to add the condition that the player can now move onto the coin symbol, in addition to this we need to track the point when we collect the coin.

2. In the Maze class  we need to edit our member variables and add where we need to add the coinx and coiny and coinsymbol, this also means that we need to change out constructor to not only initialize these values on object creation but to also make the coin when the maze object is made.

3. This means that we need to change the instances made in the main function to reflect the new constructor requirements.

4. With your detection method when you run calcMazeStats and factor in the coin being collected these three things should be printed; the distance traveled from the start to the coin, on what move it was found on (number) and what direction you moved into the coin.

For a bonus point:
change number 4 to have it show the distance from the start to the coin then print the distance traveled from the coin to the end AND write in the resetMaze function AND show a completed solution to maze 2. **This must be completed In Lab**.

**_Show your TA your work to finish the lab._**

For keeping a record of your completed labs, you should also submit your code here on Canvas.
Download your .cpp file and upload it to the assignment page before submitting. Make sure the author names are listed at the top of each file!
