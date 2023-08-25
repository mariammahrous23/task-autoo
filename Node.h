#ifndef NODE_H
#define NODE_H
#include <cmath>

class Node {
public:
    int x;          // X (row) coordinate of the node on the grid
    int y;          // Y (col) coordinate of the node on the grid
    bool walkable;  // Whether the node is an walkable or not

    // Cost variables for A* algorithm
    double gCost;   // Cost from start node to this node
    double hCost;   // Estimated cost from this node to goal node
    double fCost;   // Sum of gCost and hCost
    Node* parent;   // Parent node in the path


    // Constructor
    Node(int x=0, int y=0, bool walkable=true) //to be changed later
        : x(x), y(y), walkable(walkable), gCost(0), hCost(0), fCost(-1), parent(nullptr) {
    }

/*
    // set parent
    void setParent(Node* newParent) {
        parent = newParent;
    }

    //Get parent 
    Node* getParent() {
        return parent;
    }
*/
    // Calculate gcost in manhttan way but prefer diagonal movements
    double calculateGCost(Node* startNode) {
        int row = std::abs(x - startNode->x);
        int col = std::abs(y - startNode->y);
        gCost = std::sqrt((row * row) + (col * col));
        return gCost;
    }

    // Calculate Hcost in manhttan way but prefer diagonal movements
    double calculateHCost(Node* goalNode) {
        int row = std::abs(x - goalNode->x);
        int col = std::abs(y - goalNode->y);
        hCost = std::sqrt((row*row) +(col*col));
        return hCost;
    }

    double calculateFCost(Node* startNode, Node* goalNode) {
        fCost = calculateGCost(startNode) + calculateHCost(goalNode);
        return fCost;
    }
};

#endif // NODE_H
