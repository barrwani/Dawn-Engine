#ifndef NODE2D_H
#define NODE2D_H
#include "Node.h"
#include "../Vector2.h"

//Set up basic node2D methods
class Node2D : public Node {
public:
    //Transformation
    Vector2 position;
    Vector2 scale;
    int rotation_degrees;
    double height;
    double width;
private:
    //Directions
    Vector2 UP = Vector2(0, 1);
    Vector2 DOWN = Vector2(0,-1);
    Vector2 LEFT = Vector2(-1,0);
    Vector2 RIGHT = Vector2(1,0);
    Vector2 ZERO = Vector2(0.0f, 0.0f);
};


#endif //NODE2D_H
