#ifndef CHARACTERBODY2D_H
#define CHARACTERBODY2D_H
#include "CollisionObject2D.h"

class CharacterBody2D : public CollisionObject2D {
public:
    void collisionDetected(CollisionObject2D* col) override;
    virtual void update(float delta) override;
    bool isOnFloor() const;
    CharacterBody2D(Vector2 position, Vector2 dimension, float scale);
    ~CharacterBody2D();
    bool onFloor;
    Vector2 velocity;

};


#endif //CHARACTERBODY2D_H
