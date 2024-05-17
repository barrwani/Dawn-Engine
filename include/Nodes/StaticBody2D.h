#ifndef STATICBODY2D_H
#define STATICBODY2D_H
#include "CollisionObject2D.h"

class StaticBody2D : public CollisionObject2D {
public:
    void collisionDetected(CollisionObject2D* col) override;
    void update() override;
    StaticBody2D(Vector2 position, Vector2 dimension, float scale);
    ~StaticBody2D();
};


#endif //STATICBODY2D_H
