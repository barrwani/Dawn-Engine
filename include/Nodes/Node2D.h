#ifndef NODE2D_H
#define NODE2D_H
#include "Node.h"
#include "../Vector2.h"


//Set up basic node2D methods
class Node2D : public Node {
public:
    Node2D(Vector2 position, Vector2 scale);
    Node2D();

    //Transformations
    Vector2 position,direction,scale,lastPosition;
    int rotation_degrees;



    virtual void draw() override;
    virtual void update() override;
    virtual int getWidth() const {return scale.x;}
    virtual int getHeight() const {return scale.y;}
    Vector2 getScale() const {return scale;}


protected:
    //Directions
    Vector2 UP = Vector2(0, 1);
    Vector2 DOWN = Vector2(0,-1);
    Vector2 LEFT = Vector2(-1,0);
    Vector2 RIGHT = Vector2(1,0);
    Vector2 ZERO = Vector2(0.0f, 0.0f);
    int speed;
};


#endif //NODE2D_H
