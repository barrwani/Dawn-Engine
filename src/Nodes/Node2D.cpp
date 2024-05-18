#include "../../include/Nodes/Node2D.h"


Node2D::Node2D(Vector2 position, Vector2 dimension, float scale)
{
    position = position;
    dim = dimension;
    scale = scale;
    direction = Vector2(0,0);
    rotation_degrees = 0;
}



Node2D::Node2D()
{
    position = Vector2(0, 0);
    scale = 1;
    dim = Vector2(32,32);
    direction = Vector2(0,0);
    rotation_degrees = 0;
}

void Node2D::draw()
{

}

void Node2D::updateChildren()
{
    for(auto& child : children)
    {
        if(!child){continue;}
        child->setPosition(position);
        child->setDirection(direction);
        child->update();
    }
}

void Node2D::update()
{
    //Normalise the direction vector, same speed all directions
    direction.Normalise();

    //Move the entity
    position.x += direction.x * speed;
    position.y += direction.y * speed;
}