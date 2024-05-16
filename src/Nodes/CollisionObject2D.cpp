
#include "../../include/Nodes/CollisionObject2D.h"

CollisionObject2D::CollisionObject2D(Vector2 position, Vector2 scale)
{
    CollisionShape2D.x = position.x;
    CollisionShape2D.y = position.y;
    CollisionShape2D.w = scale.x;
    CollisionShape2D.h = scale.y;
    //Default square for src rect
    srcRect = {0,0,32,32};
    //dest rect set to collider rect
    destRect = {CollisionShape2D.x, CollisionShape2D.y, CollisionShape2D.w, CollisionShape2D.h};
}

CollisionObject2D::CollisionObject2D()
{
    CollisionShape2D = {0,0,0,0};
    srcRect = {0,0,0,0};
    destRect = {0,0,0,0};
}
void CollisionObject2D::addCollisionLayer(int layer)
{
    if(!collisionlayers[layer])
        collisionlayers[layer] = true;
}

void CollisionObject2D::removeCollisionLayer(int layer)
{
    if(collisionlayers[layer])
        collisionlayers[layer] = false;
}

void CollisionObject2D::draw()
{
    //nothing yet
}


bool CollisionObject2D::checkCollision(const CollisionObject2D &other)
{
    return Collision::AABB(CollisionShape2D, other.CollisionShape2D);
}


void CollisionObject2D::update()
{
    destRect = CollisionShape2D;
}



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

