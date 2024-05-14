
#include "../include/Collision.h"

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{
    if(recA.x + recA.w >= recB.x &&
       recB.x + recB.w >= recA.x &&
       recA.y + recA.h >= recB.y &&
       recB.y + recB.h >= recA.y)
    {
        return true;
    }
    return false;
}

bool Collision::AABB(const CollisionObject2D& colA, const CollisionObject2D& colB)
{
    if(AABB(colA.getCollider(), colB.getCollider()))
    {
        return true;
    }
    return false;
}
