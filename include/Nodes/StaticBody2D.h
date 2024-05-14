#ifndef STATICBODY2D_H
#define STATICBODY2D_H
#include "CollisionObject2D.h"

class StaticBody2D : public CollisionObject2D {
public:
    void collisionDetected();
    StaticBody2D();
    ~StaticBody2D();
};


#endif //STATICBODY2D_H
