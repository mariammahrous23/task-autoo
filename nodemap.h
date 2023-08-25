#pragma once
#include "node.h"
#include "warehouse.h"

class nodemap
{
public:
Node * closed[121];
int closedsize;
int opensize;
Node * open[121]; //max size, can be better optimised if linkedlist

nodemap() : closedsize(0), opensize(0)
{
   Node nodemap[__privates::mapSize][__privates::mapSize]; 
   for (int row = 0; row < __privates::mapSize; row++)
    {
        for (int col = 0; col < __privates::mapSize; col++)
        {
            bool iswalakable = __privates::map[row][col];
            Node temp(row,col,iswalakable);
            nodemap[row][col]=temp;
        }            
    }
}

Node* getminfcost(Node *open[], int size) //needs more validation
{
    Node* temp = nullptr;
    int min = 100000000000000; //dummy very large number, should be inf or 1st element
    for (int i=0; i<size; i++)
    {
        if (open[i]->fCost!=-1 && open[i]->fCost < min)
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
            open[i]=open[size-1];
            open[size-1]=nullptr;
            size--;
            break;
        }
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



};
