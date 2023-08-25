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
//#include "stack.h"
#include <stack>


Node nodemap[__privates::mapSize][__privates::mapSize]; 

void initialize() 
{
   /*for (int row = 0; row < __privates::mapSize; row++)
    {
        for (int col = 0; col < __privates::mapSize; col++)
        {
            bool iswalakable = __privates::map[row][col];
            Node temp(row,col,iswalakable);
            nodemap[row][col]=temp;
        }            
    }*/

    //grid -> nodes in 2D array or map grid
    /*
    This function will run after the warehouse is loaded.
    */
}

Node* getminfcost(Node *open[], int size) //needs more validation
{
    Node* temp = nullptr;
    int min = 276447232; //dummy very large number, should be inf or 1st element
    for (int i=0; i<size; i++)
    {
        if (open[i]->fCost < min)
        {
            min = open[i]->fCost;
            temp = open[i];
        }
    }
    return temp;
}

void removeFromOpen(Node *open[],Node * current, int &size)
{
    for(int i=0; i<size; i++)
    {
        if (open[i]->x==current->x && open[i]->y==current->y) //ashyak b operator overload
        {
            size--;
            open[i]=open[size];
            open[size+1]=nullptr;
            break;
        }
        // 
    }
}

bool isInClosed(Node* closed[], Node* neighbour, int size)
{
    for(int i=0; i<size; i++)
    {
        if (closed[i]->x == neighbour->x && closed[i]->y == neighbour->y)
        {
            return true;
        }
    }
    return false;
}

bool isInOpen(Node* open[], Node* neighbour, int size)
{
    for(int i=0; i<size; i++)
    {
        if (open[i]->x == neighbour->x && open[i]->y == neighbour->y)
        {
            return true;
        }
    }
    return false;
}


void goTo (Node * togoptr , Node * startptr)
{
     for (int row = 0; row < __privates::mapSize; row++)
    {
        for (int col = 0; col < __privates::mapSize; col++)
        {
            bool iswalakable = __privates::map[row][col];
            Node temp(row,col,iswalakable);
            nodemap[row][col]=temp;
        }            
    }


   std::stack<Node*> path;
 
    Node * closed[121];
    int closedsize =0;
    Node * current = &nodemap[__privates::robotPos.row][__privates::robotPos.col];
    Node * open[121]; //max size, can be better optimised if linkedlist
    open[0]=current;
    current->calculateFCost(startptr,togoptr);
    int opensize=1;
    bool reached = (current->x ==togoptr->x) && (current->y == togoptr->y);;
    //Node * MinFcostNode = nullptr; //for comparison with neighbours
    while(!reached)
    {
        current = getminfcost(open, opensize);
        removeFromOpen(open,current,opensize);
        closed[closedsize] = current;
        closedsize++;
        //traversing the 8 neighbouring cells of the 'current'
        for(int i=-1; i<=1; i++)
        {
           
            for(int j=-1; j<=1; j++)
            {
                int r = (current->x) - i;
                int c = (current->y) - j;
                if(r<0 || r>10 ||c <0 || c>10)
                    {continue;}
                else
                {
                    Node * neighbour = & nodemap[r][c];
                    if(!neighbour->walkable || isInClosed(closed,neighbour,closedsize))
                    {continue;}
                    //|| neighbour->calculateFCost(startptr,togoptr)<getminfcost(open, opensize)->calculateFCost(startptr,togoptr)
                    else if(!isInOpen(open,neighbour,opensize))
                    {
                        neighbour->calculateFCost(startptr,togoptr);
                        neighbour->parent= current;
                        open[opensize]=neighbour;
                        opensize++;
                    
                    }
                }
            }

        }
        // print maze byza mn abl hena bardo
       if ((current->x ==togoptr->x) && (current->y == togoptr->y))
        {
            path.push(current); //The goal 
            while (current->parent) 
            { 
                path.push(current->parent) ; 
                current = current->parent ; 
            } 
            reached=true;
            break;
        }
    }      


    //by the end of this loop, robot has picked up the item and the current = pickup pos
    //now we recurse back with parents and put the nodes in a stack
    //Stack<Node*> path;
    //std::stack<Node*> path;
    //generatepath(path,current);
    //now that the stack contains or nodes to the path
    //time to move robot by popping the nodes, calculating relative pos, giving it to the robot
    //pop , calc rel pos, move robot, get next, do again
    Node* nextmove = path.top();
    path.pop();
    while (!path.empty())
    {
        int movex = nextmove->x - getRobotPos().col;
        int movey = nextmove->y - getRobotPos().row;
        moveRobot(movex,movey);
        printMaze();
        nextmove = path.top();
        path.pop();
    
    }
}

void solve() 
{
   Node pickup(getItemPos().col,getItemPos().row,true);
    Node * pickptr = &pickup;
    Node goal(getGoalPos().col, getGoalPos().row,true);
    Node* goalptr = &goal;
   Node start(getRobotPos().col, getRobotPos().row,true);
    Node* startptr = &start;
    goTo(pickptr,startptr);
    //int movex= getItemPos().col - getRobotPos().col;
    //int movey= getItemPos().row - getRobotPos().row;
    //moveRobot(movex,movey);
    printMaze();
    bool p = pickItem();
    goTo(goalptr,startptr);
    // movex= getGoalPos().col - getRobotPos().col;
    //  movey= getGoalPos().row - getRobotPos().row;
     // moveRobot(movex,movey);
    printMaze();
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