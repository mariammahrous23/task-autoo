/*
The goal of this task is to develop an algorithm to solve a warehouse (reach a goal) without knowing
the warehouse as a whole from the get-go, you will need to explore the warehouse step by step.

You have to include "warehouse.h".

Your code goes in the initialize and solve functions. Read the instructions there carefully.

Compile your code using any c++ compiler and pass level filename as an argument, for example:
g++ main.cpp -o main.exe
main.exe warehouse1.txt
*/

#include "warehouse.h"
#include "Node.h"
#include "Stack.h"

//FOR now global 

void initialize()
{
    /*
    This function will run after the warehouse is loaded.
    */
}

Node * MinOpenNode (Node * openlist[] , int actualsize )
{
    int min = 276447231;
    Node * tempmin;
    for (int i = 0 ; i < actualsize ; i++)
    {
        if (min > openlist[i]->fCost)
        {
            min = openlist[i]->fCost;
            tempmin = openlist[i];
        }
    }
    return tempmin;
}

void removecurrent (Node * openlist[] , int &actualsize, Node * current)
{
     for (int i = 0 ; i < actualsize ; i++)
    {
        if (current->x == openlist[i]->x && current->y == openlist[i]->y)
        {
            actualsize--;
            openlist[i] = openlist[actualsize];
            openlist[actualsize+1] = nullptr;

        }
    }
}

bool isInClosed(Node* closedlist[], Node* neighbour, int actualclosedsize)
{
    for(int i=0; i<actualclosedsize; i++)
    {
        if (closedlist[i]->x == neighbour->x && closedlist[i]->y == neighbour->y)
        {
            return true;
        }
    }
    return false;
}
bool isInOpen(Node* openlist[], Node* neighbour, int actualopensize)
{
    for(int i=0; i<actualopensize; i++)
    {
        if (openlist[i]->x == neighbour->x && openlist[i]->y == neighbour->y)
        {
            return true;
        }
    }
    return false;
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

    // 2D ARRAY / MAP
     Node  Grid [11][11];
      for (int row = 0; row < 11; row++)
        {
            for (int col = 0; col < 11; col++)
            {
                // getting if this is walkable
                bool tempwalkable = __privates::map[row][col]; 
                Node temp (row,col,tempwalkable);
                Grid[row][col] = temp; 
            }
        }



    // open list (kol hagat hawlena mro7nlha4)
    int actualopensize = 1 ; //because i will automatically add the robot pos
    Node * openlist [121]; 

    // Adding robot position to open list
    Point R = getRobotPos();
    Node * current = &Grid [R.row][ R.col];
    openlist[0] = current;

    // Start ptr
    Node start (R.row , R.col , true);
    Node * startptr = &start;

    // closed list  (kol el ro7nlo)
    Node * closedlist [121];
    int actualclosedsize = 0 ; 


    bool goalnotyetfound = true;
    Point G = getGoalPos(); 
    Node Goal (G.row , G.col , true);
    Node * Goalptr = &start;

    //Algorthim
    while (goalnotyetfound)
    {
        current = MinOpenNode(openlist,actualopensize);
        removecurrent(openlist,actualopensize,current);
        closedlist[actualclosedsize]=current;
        actualclosedsize++;

        for (int i = -1 ; i <= 1 ; i++)
        {
           for (int j = -1 ; i <= 1 ; i++)
            { 
                int r = (current->x) - i;
                int c = (current->y) - j;
                Node * neighbour = & Grid[r][c];
                if ( !neighbour->walkable || isInClosed(closedlist , neighbour ,actualclosedsize )  )
                {
                    //ABS NOTHING
                }
                else if (!isInOpen(openlist , neighbour, actualopensize))
                {
                    neighbour->calculateFCost(startptr,Goalptr);
                    neighbour->parent = current ;
                    openlist[actualopensize] = neighbour; 
                    actualopensize ++ ; 
                }
              
            }
        }

        if (current->x == G.row && current->y == G.col)
        {
            goalnotyetfound=false;
            break;
        }
    }
    

    // save path bl stack (nrg3 bl parent recursion ba) 

    // pop  when movement 
    // when pushing relative position (ndyha ll move robot)
    
}

int main(int argc, char const *argv[])
{
    // Initalize level
    Stack<int> myStack;
    myStack.push(10);
    cout<< myStack.pop(); 
    cout<<endl;
    initMaze(argv[1]);

    initialize();
  
    while (true)
    {
        // Check reached goal
        if (hasReachedGoal())
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