#ifndef AREA2D_H
#define AREA2D_H
#include "CollisionObject2D.h"

class Area2D : public CollisionObject2D {
public:
    void collisionDetected();
    Area2D();
    ~Area2D();
};


#endif //AREA2D_H
