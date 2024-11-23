#include "../../include/Nodes/CharacterBody2D.h"
#include "../../include/base/root.h"


CharacterBody2D::CharacterBody2D(Vector2 pos, Vector2 dim, float sc)
{
    root::colliders.insert(this);
    type = 2;
    name = "CharacterBody2D";
    position = pos;
    scale = sc;
    CollisionShape2D.x = pos.x;
    CollisionShape2D.y = pos.y;
    CollisionShape2D.w = dim.x;
    CollisionShape2D.h = dim.y;
    //Default square for src rect
    srcRect = {0,0,32,32};
    //dest rect set to collider rect
    destRect = {CollisionShape2D.x, CollisionShape2D.y, CollisionShape2D.w, CollisionShape2D.h};
}

CharacterBody2D::~CharacterBody2D()
{
    SDL_DestroyTexture(texture);
    root::colliders.remove(this);
    //make sure to destroy coltex
    //trivial for now
}

void CharacterBody2D::update(float delta)
{

    updateCollisionShape2D();


    for(auto& child : children)
    {
        child->update(delta);
        child->setPosition(position);
        child->setDirection(direction);
    }
}

bool CharacterBody2D::isOnFloor() const {return onFloor;}



void CharacterBody2D::collisionDetected(CollisionObject2D* col)
{
    colliding = true;
    int overlapLeft = (CollisionShape2D.x + CollisionShape2D.w) - col->CollisionShape2D.x;
    int overlapRight = (col->CollisionShape2D.x + col->CollisionShape2D.w) - CollisionShape2D.x;
    int overlapTop = (CollisionShape2D.y + CollisionShape2D.h) - col->CollisionShape2D.y;
    int overlapBottom = (col->CollisionShape2D.y + col->CollisionShape2D.h) - CollisionShape2D.y;

    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;

    int minOverlapX = fromLeft ? overlapLeft : overlapRight;
    int minOverlapY = fromTop ? overlapTop : overlapBottom;

    // Resolve collision by moving the player out of collision
    if (minOverlapX < minOverlapY) {
        int displacementX = fromLeft ? -overlapLeft : overlapRight;
        position.x += displacementX;
        CollisionShape2D.x += displacementX;
    } else {
        int displacementY = fromTop ? -overlapTop : overlapBottom;
        position.y += displacementY;
        CollisionShape2D.y += displacementY;

    }
}

