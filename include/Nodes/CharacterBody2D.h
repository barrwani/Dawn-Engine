#ifndef CHARACTERBODY2D_H
#define CHARACTERBODY2D_H
#include "CollisionObject2D.h"

class CharacterBody2D : public CollisionObject2D {
public:
    void collisionDetected(CollisionObject2D* col) override;
    virtual void update() override;
    void updatePosition();
    CharacterBody2D(Vector2 position, Vector2 dimension, float scale);
    ~CharacterBody2D();
};


#endif //CHARACTERBODY2D_H
