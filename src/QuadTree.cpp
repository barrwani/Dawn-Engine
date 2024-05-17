#include "../include/QuadTree.h"

QuadTree::QuadTree(int level, int x, int y, int w, int h) : level(level), x(x), y(y), w(w), h(h)
{}

void QuadTree::clear()
{
    collision_nodes.clear();
    nodes.clear();
}
void QuadTree::split()
{
    int subWidth = w / 2;
    int subHeight = h / 2;
    int xMid = x + subWidth;
    int yMid = y + subHeight;

    nodes.push_back(std::make_unique<QuadTree>(level + 1, x, y, subWidth, subHeight));
    nodes.push_back(std::make_unique<QuadTree>(level + 1, xMid, y, subWidth, subHeight));
    nodes.push_back(std::make_unique<QuadTree>(level + 1, x, yMid, subWidth, subHeight));
    nodes.push_back(std::make_unique<QuadTree>(level + 1, xMid, yMid, subWidth, subHeight));
}

int QuadTree::getIndex(CollisionObject2D *collision_node)
{
    int index = -1;
    double vertMidpoint  = x + (w/2);
    double horMidpoint = y + (h/2);

    bool topQuadrant = (collision_node->CollisionShape2D.y < horMidpoint
            && collision_node->CollisionShape2D.y + collision_node->CollisionShape2D.h < horMidpoint);
    bool bottomQuadrant = (collision_node->CollisionShape2D.y > horMidpoint);

    if(collision_node->CollisionShape2D.x < vertMidpoint &&
    collision_node->CollisionShape2D.x + collision_node->CollisionShape2D.w < vertMidpoint)
    {
        if(topQuadrant)
        {
            index = 0;
        }else if (bottomQuadrant)
        {
            index = 2;
        }
    }else if(collision_node->CollisionShape2D.x > vertMidpoint)
    {
        if(topQuadrant)
        {
            index = 1;
        }else if (bottomQuadrant)
        {
            index = 3;
        }
    }
    return index;
}

void QuadTree::insert(CollisionObject2D *collision_node)
{
    if(!nodes.empty())
    {
        int index = getIndex(collision_node);
        if(index !=-1)
        {
            nodes[index]->insert(collision_node);
            return;
        }
    }
    collision_nodes.push_back(collision_node);

    if(collision_nodes.size()> MAX_COL_NODES && level < MAX_LEVELS)
    {
        if(nodes.empty())
        {
            split();
        }

        auto iter = collision_nodes.begin();
        while(iter != collision_nodes.end())
        {
            int index = getIndex(*iter);
            if(index != -1)
            {
                nodes[index]->insert(*iter);
                iter = collision_nodes.erase(iter);
            }
            else{++iter;}
        }
    }
}
void QuadTree::retrieve(std::vector<CollisionObject2D*>& returnCols, CollisionObject2D* collision_node) {
    int index = getIndex(collision_node);
    if (index != -1 && !nodes.empty()) {
        nodes[index]->retrieve(returnCols, collision_node);
    }
    returnCols.insert(returnCols.end(), collision_nodes.begin(), collision_nodes.end());
}


void QuadTree::checkCollisions() {
    if (!nodes.empty()) {
        for (const auto& node : nodes) {
            node->checkCollisions();
        }
    }

    for (CollisionObject2D* col1 : collision_nodes) {
        std::vector<CollisionObject2D*> potentialCollisions;
        retrieve(potentialCollisions, col1);
        for (CollisionObject2D* col2 : potentialCollisions) {
            if (col1 != col2 && col1->checkCollision(*col2) && col1->collision && col2->collision) {
                col1->collisionDetected(col2);
                col2->collisionDetected(col1);
            }
        }
    }
}