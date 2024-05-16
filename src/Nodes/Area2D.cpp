#include "../../include/Nodes/Area2D.h"
#include "../../include/root.h"

Area2D::Area2D(Vector2 p, Vector2 s)
{
    name = "area2D";
    position = p;
    scale = s;
    CollisionShape2D.x = p.x;
    CollisionShape2D.y = p.y;
    CollisionShape2D.w = s.x;
    CollisionShape2D.h = s.y;
    //Default square for src rect
    srcRect = {0,0,32,32};
    //dest rect set to collider rect
    destRect = {CollisionShape2D.x, CollisionShape2D.y, CollisionShape2D.w, CollisionShape2D.h};
}

Area2D::~Area2D()
{
    //make sure to destroy coltex
    //trivial for now
}

void Area2D::update()
{
    destRect.x = static_cast<int>(position.x - root::camera.x);
    destRect.y = static_cast<int>(position.y - root::camera.y);
    destRect.w = getWidth() * getScale().x;
    destRect.h = getHeight() * getScale().y;
}

void Area2D::collisionDetected(CollisionObject2D* col)
{

}

