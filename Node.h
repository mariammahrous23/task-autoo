#ifndef NODE_H
#define NODE_H
#include <cmath>

class Node {
public:
    int x;          // X (row) coordinate of the node on the grid
    int y;          // Y (col) coordinate of the node on the grid
    bool walkable;  // Whether the node is an obstacle or not

    // Cost variables for A* algorithm
    double gCost;   // Cost from start node to this node
    double hCost;   // Estimated cost from this node to goal node
    double fCost;   // Sum of gCost and hCost

    Node* parent;   // Parent node in the path

    // constructor
    Node(int x, int y, bool obstacle = false)
        : x(x), y(y), obstacle(obstacle), gCost(0), hCost(0), fCost(0), parent(nullptr) {
    }

    

    void setParent(Node* newParent) {
        parent = newParent;
    }

    // Calculate gcost in manhttan way but prefer diagonal movements
    void calculateGCost(Node* startNode) {
    int row = std::abs(x - startNode->x);
    int col = std::abs(y - startNode->y);
    gCost = row + col; 
    }   

    // Calculate Hcost in manhttan way but prefer diagonal movements
   void calculateHCost(Node* goalNode) {
    int row = std::abs(x - goalNode->x);
    int col = std::abs(y - goalNode->y);
    hCost = row + col ;
    }

    double calculateFCost( Node* startNode , Node* goalNode ) {
        fCost = calculateGCost(startNode) + calculateHCost(goalNode);
        return fCost;
    }
};

#endif // NODE_H
