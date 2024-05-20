#include "../../include/Nodes/Area2D.h"
#include "../../include/base/root.h"

Area2D::Area2D(Vector2 p, Vector2 dim, float sc)
{
    root::colliders.insert(this);
    name = "area2D";
    type = 1;
    position = p;
    scale = sc;
    CollisionShape2D.x = p.x;
    CollisionShape2D.y = p.y;
    CollisionShape2D.w = dim.x;
    CollisionShape2D.h = dim.y;
    //Default square for src rect
    srcRect = {0,0,32,32};
    //dest rect set to collider rect
    destRect = {CollisionShape2D.x, CollisionShape2D.y, CollisionShape2D.w, CollisionShape2D.h};
}

Area2D::~Area2D()
{
    root::colliders.remove(this);
    SDL_DestroyTexture(texture);
    //make sure to destroy coltex
    //trivial for now
}

void Area2D::update(float delta)
{
    colliding = false;
    destRect.x = static_cast<int>(position.x - root::camera.x);
    destRect.y = static_cast<int>(position.y - root::camera.y);
    destRect.w = getWidth() * getScale();
    destRect.h = getHeight() * getScale();
}

void Area2D::collisionDetected(CollisionObject2D* col)
{
    colliding = true;

}

