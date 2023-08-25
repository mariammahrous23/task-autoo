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
#include <stack>


//FOR now global 
std::stack<Node*> path;

void initialize()
{
    /*
    This function will run after the warehouse is loaded.
    */
}

Node * MinOpenNode (Node * openlist[] , int actualsize )
{
    //Get the node with minumum F cost 
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
    //After the node is processed remove it from Openlist
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
    //Check if node is already in close
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
    //Check if node is already in Open
    for(int i=0; i<actualopensize; i++)
    {
        if (openlist[i]->x == neighbour->x && openlist[i]->y == neighbour->y)
        {
            return true;
        }
    }
    return false;
}

void Getpath(Node * startptr , Node * Goalptr)
{
    // making the 2D map to be able to access 
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
    Node * openlist [121]; //Max no 11*11
    Node * current = &Grid [startptr->x][startptr->y];
    openlist[0] = current;

     // closed list  (kol el ro7nlo)
    Node * closedlist [121];
    int actualclosedsize = 0 ;
    bool goalnotyetfound = true; // intially nothing is found
    
    // A* Algorthim
    while (goalnotyetfound)
    {
        current = MinOpenNode(openlist,actualopensize);
        removecurrent(openlist,actualopensize,current);
        closedlist[actualclosedsize]=current;
        actualclosedsize++;
    //Exploring it's neighbours
     for (int i = -1 ; i <= 1 ; i++)
       {
           for (int j = -1 ; j <= 1 ; j++)
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


        // save path inside the stack (nrg3 bl parent) 
        if (current->x == Goalptr->x && current->y == Goalptr->y )
        {
            goalnotyetfound=false; //Goal is found
            path.push(current); //The goal 
            while (current->parent) 
            { 
                path.push(current->parent) ; 
                current = current->parent ; 
            } 
            break;
        }
    }

    // pop when movement 
    while (!path.empty()) 
    { 
     Node * move= path.top(); 
     path.pop();
     // Intially right, down movements

     // (1) Up and (-1) down movement 
     int r = (move->x) - (startptr->x) ; 
     
     // (1) right and (-1) left movement
     int c = (move->y) - (startptr->y) ; 

     moveRobot(c,r); 
    } 


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


    // Robot, Goal,pickup
    Point R = getRobotPos();
    Node start (R.row , R.col , true);
    Node * startptr = &start;

    Point G = getGoalPos(); 
    Point P = getItemPos(); 
    Node Goal (G.row , G.col , true);
    Node Pick (P.row , P.col , true);
    if (pickItem())
    {
        Node * Goalptr = &Goal;
        Getpath(startptr ,Goalptr );
    }
    else 
    {
        Node * Goalptr = &Pick;
        Getpath(startptr ,Goalptr );
    }
   
    
}

int main(int argc, char const *argv[])
{
    // Initalize level
    initMaze(argv[1]);

    initialize();
  
    while (true)
    {
        // Check reached goal
        if (hasReachedGoal())
        {
            // Hurray!
            PrintMaze();
            cout << "Reached Goal!" << endl;
            break;
        }

        // Solve maze
        solve();
    }

    return 0;
}
