/*
The goal of this task is to develop an algorithm to solve a warehouse (reach a goal) without knowing
the warehouse as a whole from the get-go, you will need to explore the warehouse step by step.

You have to include "warehouse.h".

Your code goes in the *initialize* and *solve* functions. Read the instructions there carefully.

Compile your code using any c++ compiler and pass level filename as an argument, for example:
g++ main.cpp -o main.exe
main.exe warehouse1.txt
*/

#include "warehouse.h"
#include <vector>


//GLOBAL VARIABLES 
//CHECK IF THIS CAN BE DONE
bool Pfound = false;
bool Gfound = false;

void initialize()
{
    /*
    This function will run after the warehouse is loaded.
    */

    //Creating the map in 2D MATRIX
    int MS = __privates::mapSize; // MS for matrix size
    std::vector<std::vector<char>> matrix(MS, std::vector<char>(MS));

    for (int row = 0; row < MS; row++)
    {
        for (int col = 0; col < MS; col++)
        {
            if (__privates::robotPos.row == row && __privates::robotPos.col == col)
                matrix[row][col] = '>' ;
            else if (__privates::goalPos.row == row && __privates::goalPos.col == col)
                matrix[row][col] = 'D' ;
            else if (__privates::pickupPos.row == row && __privates::pickupPos.col == col && !__privates::hasItem)
                matrix[row][col] = 'P' ;
            else
                 matrix[row][col] = (__privates::map[row][col] ? '.' : '#');
        }
    }
       for (int row = 0; row < MS; row++)
    {
        for (int col = 0; col < MS; col++)
        {
            cout << matrix [row][col];
        }
    }
}

void solve2(Point D , Point R )
{
    /* Because we won't repeat the same code twice
    It should take current robot position and Destantion (Pickup or Goal)
    */
}

void solve()
{
    /*
    This function will keep running forever until the goal is reached.

    You can access the warehouse API through below functions.

    Sense and Control:
        isWalkable(right, down): checks if cell around robot is walkable (right: [-1 0 1], down: [-1 0 1])
        moveRobot(right, down): moves player one step (right: [-1 0 1], down: [-1 0 1])

    Global Info:
        getRobotPos(): gets robot position in warehouse
        getGoalPos()  : gets goal position in warehouse
        getItemPos() : gets item position in warehouse

    Debugging:
        printMaze()  : prints warehouse as a whole
        printAround(): prints part of warehouse around robot
    */

  Point R = getRobotPos();
  Point P =getItemPos();
  Point G =getGoalPos();

  if (R.row == P.row && R.col == P.col)
  {
    solve2(G,R);
    Pfound = true ;
  }
  else if (R.row == G.row && R.col == G.col)
  {
    Gfound = true;
  }
  else if (Pfound)
  {
    solve2(G,R);
  }
  else 
  {
    solve2(P,R);
  }


   
}


int main(int argc, char const *argv[])
{
    // Initalize level
    initMaze(argv[1]);

    initialize();

    // Game loop
    while (true)
    {
        // Check reached goal
        if (hasReachedGoal()) //Doesn't seem to be working
        {
            // Hurray!
            cout << "Reached Goal!" << endl;
            break;
        }

        if (Gfound) 
        {
            // Hurray!
            cout << "Reached Goal!" << endl;
           break;
        }

        // Solve maze
        solve();
    }

    return 0;
}