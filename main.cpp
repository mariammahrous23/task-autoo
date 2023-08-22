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

//GLOBAL VARIABLES 
//CHECK IF THIS CAN BE DONE
bool Pfound = false;
bool Gfound = false;


void initialize()
{
    /*
    This function will run after the warehouse is loaded.
    */
    // Honestly have no idea what to do here
}

void solve2(Point D , Point R )
{

  /*
  The shortest way if there is no obstacles to move diagonally if it possible 
  //to move diagonally R/P/G must be like (x,x) and (y,y) vertices
  */
 
 // This will move diagnoally if possible at any time 

    if (R.row > D.row )
    {
        if(isWalkable(-1,-1))
        {
            moveRobot(-1,-1);
        }
    }
    else if (R.row < D.row )
    {
        if(isWalkable(1,1))
        {
            moveRobot(1,1);
        }
    }

  
 

  //Diagonal isn't an option 


    printMaze();
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