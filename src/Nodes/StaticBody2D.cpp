#include "../../include/Nodes/StaticBody2D.h"
#include "../../include/base/root.h"

StaticBody2D::StaticBody2D(Vector2 p, Vector2 d, float sc)
{
    root::colliders.insert(this);
    scale = sc;
    type = 0;
    visiblecollision = true;
    name = "staticbody2D";
    position = p;
    dim = d;
    CollisionShape2D.x = position.x;
    CollisionShape2D.y = position.y;
    CollisionShape2D.w = dim.x;
    CollisionShape2D.h = dim.y;
    //Default square for src rect
    srcRect = {0,0,32,32};
    //dest rect set to collider rect
    destRect = {CollisionShape2D.x, CollisionShape2D.y, CollisionShape2D.w, CollisionShape2D.h};
}


StaticBody2D::~StaticBody2D()
{
    root::colliders.remove(this);
    SDL_DestroyTexture(texture);
    //make sure to destroy coltex
    //trivial for now
}

void StaticBody2D::update(float delta)
{
    destRect.x = static_cast<int>(position.x - root::camera.x);
    destRect.y = static_cast<int>(position.y - root::camera.y);
    destRect.w = getWidth() * getScale();
    destRect.h = getHeight() * getScale();
}

void StaticBody2D::collisionDetected(CollisionObject2D* col)
{

}

