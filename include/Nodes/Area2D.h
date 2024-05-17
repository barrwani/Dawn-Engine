#ifndef AREA2D_H
#define AREA2D_H
#include "CollisionObject2D.h"

class Area2D : public CollisionObject2D {
public:
    void collisionDetected(CollisionObject2D* col) override;
    Area2D();
    ~Area2D();
    void update() override;
    Area2D(Vector2 p, Vector2 dim, float sc);
};


#endif //AREA2D_H
