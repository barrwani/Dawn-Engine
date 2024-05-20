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
    int rotation_degrees;
    float scale;

    Vector2 getPosition() override{return position;}
    Vector2 getDirection() override{return direction;}
    Vector2 getDimension() override{return dim;}


    void updateChildren(float delta);

    void setPosition(Vector2 newpos) override{position = newpos;}
    void setDirection(Vector2 newdir) override{direction = newdir;}
    void setDimension(Vector2 newdim) override{dim = newdim;}

    virtual void draw() override;
    virtual void update(float delta) override;
    virtual int getWidth() const {return dim.x;}
    virtual int getHeight() const {return dim.y;}
    float getScale() const {return scale;}


protected:
    int speed = 3;
    Vector2 position,direction, dim;

};


#endif //NODE2D_H
