#ifndef COLLISIONOBJECT2D_H
#define COLLISIONOBJECT2D_H

#include "Node2D.h"

class CollisionObject2D : public Node2D{
public:
    SDL_Rect getCollider() const {return CollisionShape2D;}
    virtual void collisionDetected() = 0;
private:
    SDL_Rect CollisionShape2D;
    bool visible;

};


#endif //COLLISIONOBJECT2D_H
