#include "../../include/Nodes/CharacterBody2D.h"
#include "../../include/root.h"


CharacterBody2D::CharacterBody2D(Vector2 pos, Vector2 dim, float sc)
{
    type = 2;
    name = "characterbody2D";
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
    //make sure to destroy coltex
    //trivial for now
}

void CharacterBody2D::update()
{
    updateCollisionShape2D();

    updatePosition();

    for(auto& child : children)
    {
        child->update();
        child->position = position;
        child->direction = direction;
    }
}

void CharacterBody2D::updatePosition()
{
    direction.Normalise();

    lastPosition = position;

    //Move the entity
    position.x += direction.x * speed;
    position.y += direction.y * speed;

}
void CharacterBody2D::collisionDetected(CollisionObject2D* col)
{
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

