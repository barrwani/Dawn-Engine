#ifndef NODE2D_H
#define NODE2D_H
#include "Node.h"
#include "../Vector2.h"


//Set up basic node2D methods
class Node2D : public Node {
public:
    Node2D(Vector2 position, Vector2 dimension, float scale);
    Node2D();
    ~Node2D() override =default;

    //Transformations
    Vector2 position,direction,dim,lastPosition;
    int rotation_degrees;
    float scale;



    virtual void draw() override;
    virtual void update() override;
    virtual int getWidth() const {return dim.x;}
    virtual int getHeight() const {return dim.y;}
    float getScale() const {return scale;}


protected:
    int speed = 3;
};


#endif //NODE2D_H
