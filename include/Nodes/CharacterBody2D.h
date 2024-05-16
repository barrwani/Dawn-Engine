#ifndef CHARACTERBODY2D_H
#define CHARACTERBODY2D_H
#include "CollisionObject2D.h"

class CharacterBody2D : public CollisionObject2D {
    void collisionDetected(CollisionObject2D* col) override;
    void update() override;
    std::string type = "CharacterBody2D";
    CharacterBody2D(Vector2 position, Vector2 scale);
    ~CharacterBody2D();
};


#endif //CHARACTERBODY2D_H
