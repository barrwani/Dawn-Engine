#include "../../include/Nodes/Node2D.h"


Node2D::Node2D(Vector2 position, Vector2 scale)
{
    position = position;
    scale = scale;
    direction = Vector2(0,0);
    rotation_degrees = 0;

}


Node2D::Node2D()
{
    position = Vector2(0, 0);
    scale = Vector2(1, 1);
    direction = Vector2(0,0);
    rotation_degrees = 0;
}

void Node2D::draw()
{

}

void Node2D::update()
{
    //Normalise the direction vector, same speed all directions
    direction.Normalise();

    //Set previous position, used for collision physics
    lastPosition = position;

    //Move the entity
    position.x += direction.x * speed;
    position.y += direction.y * speed;
}