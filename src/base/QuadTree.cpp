#include "../../include/base/QuadTree.h"

// Constructor initializes the quad tree node with level and dimensions.
QuadTree::QuadTree(int level, int x, int y, int w, int h) : level(level), x(x), y(y), w(w), h(h)
{}

// Clears the collision nodes and child nodes of the quad tree.
void QuadTree::clear()
{
    collision_nodes.clear(); // Clear the list of collision objects.
    nodes.clear();           // Clear the child nodes.
}

// Splits the current node into four child nodes.
void QuadTree::split()
{
    int subWidth = w / 2;   // Calculate width of child nodes.
    int subHeight = h / 2;  // Calculate height of child nodes.
    int xMid = x + subWidth; // Calculate the midpoint on the x-axis.
    int yMid = y + subHeight; // Calculate the midpoint on the y-axis.

    // Create and store four child nodes.
    nodes.push_back(std::make_unique<QuadTree>(level + 1, x, y, subWidth, subHeight));
    nodes.push_back(std::make_unique<QuadTree>(level + 1, xMid, y, subWidth, subHeight));
    nodes.push_back(std::make_unique<QuadTree>(level + 1, x, yMid, subWidth, subHeight));
    nodes.push_back(std::make_unique<QuadTree>(level + 1, xMid, yMid, subWidth, subHeight));
}

// Removes a collision node from the quad tree.
void QuadTree::remove(CollisionObject2D* collision_node)
{
    // Check if the node has child nodes to potentially remove the collision node from.
    if (!nodes.empty())
    {
        int index = getIndex(collision_node); // Get index of the child node.
        if (index != -1)
        {
            // Try to remove from the appropriate child node.
            nodes[index]->remove(collision_node);
            return;
        }
    }

    // Try to remove the collision node from the current node.
    auto iter = std::find(collision_nodes.begin(), collision_nodes.end(), collision_node);
    if (iter != collision_nodes.end())
    {
        collision_nodes.erase(iter); // Remove the collision node.
    }

    // Check if child nodes can be merged back into the parent node.
    if (!nodes.empty())
    {
        bool allChildrenEmpty = true; // Assume all children are empty.
        for (const auto& node : nodes)
        {
            // Check if any child node has collision objects or child nodes.
            if (!node->collision_nodes.empty() || !node->nodes.empty())
            {
                allChildrenEmpty = false; // Found a non-empty child node.
                break;
            }
        }

        // Clear child nodes if they are all empty.
        if (allChildrenEmpty)
        {
            nodes.clear();
        }
    }
}

// Determines the index of the quadrant the collision node belongs to.
int QuadTree::getIndex(CollisionObject2D *collision_node)
{
    int index = -1; // Initialize index to -1 (no quadrant).
    double vertMidpoint  = x + (w/2); // Calculate vertical midpoint.
    double horMidpoint = y + (h/2);    // Calculate horizontal midpoint.

    // Determine if the collision node is in the top or bottom quadrants.
    bool topQuadrant = (collision_node->CollisionShape2D.y < horMidpoint
                        && collision_node->CollisionShape2D.y + collision_node->CollisionShape2D.h < horMidpoint);
    bool bottomQuadrant = (collision_node->CollisionShape2D.y > horMidpoint);

    // Check which quadrant the collision node is in.
    if(collision_node->CollisionShape2D.x < vertMidpoint &&
       collision_node->CollisionShape2D.x + collision_node->CollisionShape2D.w < vertMidpoint)
    {
        // Left side
        if(topQuadrant)
        {
            index = 0; // Top-left quadrant.
        } else if (bottomQuadrant)
        {
            index = 2; // Bottom-left quadrant.
        }
    } else if(collision_node->CollisionShape2D.x > vertMidpoint)
    {
        // Right side
        if(topQuadrant)
        {
            index = 1; // Top-right quadrant.
        } else if (bottomQuadrant)
        {
            index = 3; // Bottom-right quadrant.
        }
    }
    return index; // Return the index of the quadrant.
}

// Inserts a collision node into the quad tree.
void QuadTree::insert(CollisionObject2D *collision_node)
{
    // Check if there are child nodes to insert into.
    if(!nodes.empty())
    {
        int index = getIndex(collision_node); // Get the index of the appropriate child node.
        if(index != -1)
        {
            nodes[index]->insert(collision_node); // Insert into the child node.
            return;
        }
    }

    // Add the collision node to the current node.
    collision_nodes.push_back(collision_node);

    // Check if the node exceeds the maximum allowed collision nodes and is not at max level.
    if(collision_nodes.size() > MAX_COL_NODES && level < MAX_LEVELS)
    {
        if(nodes.empty())
        {
            split(); // Split the current node into four child nodes.
        }

        // Move collision nodes to the appropriate child nodes.
        auto iter = collision_nodes.begin();
        while(iter != collision_nodes.end())
        {
            int index = getIndex(*iter);
            if(index != -1)
            {
                nodes[index]->insert(*iter); // Insert into the child node.
                iter = collision_nodes.erase(iter); // Remove from the current node.
            }
            else
            {
                ++iter; // Move to the next collision node.
            }
        }
    }
}

// Retrieves potential collisions for a given collision node.
void QuadTree::retrieve(std::vector<CollisionObject2D*>& returnCols, CollisionObject2D* collision_node)
{
    int index = getIndex(collision_node); // Get the index of the child's node.
    // If there's an appropriate child node, retrieve collisions from it.
    if (index != -1 && !nodes.empty())
    {
        nodes[index]->retrieve(returnCols, collision_node);
    }
    // Add the current node's collision objects to the return vector.
    returnCols.insert(returnCols.end(), collision_nodes.begin(), collision_nodes.end());
}

// Checks for collisions between all objects in the quad tree.
void QuadTree::checkCollisions()
{
    // Check collisions in child nodes recursively.
    if (!nodes.empty())
    {
        for (const auto& node : nodes)
        {
            node->checkCollisions();
        }
    }

    // Check for collisions among the collision nodes.
    for (CollisionObject2D* col1 : collision_nodes)
    {
        std::vector<CollisionObject2D*> potentialCollisions; // Store potential collisions.
        retrieve(potentialCollisions, col1); // Retrieve potential collisions for col1.

        // Check for actual collisions.
        for (CollisionObject2D* col2 : potentialCollisions)
        {
            // Ensure col1 and col2 are not the same and check for a collision.
            if (col1 != col2 && col1->checkCollision(*col2) && col1->collision && col2->collision)
            {
                // Notify both objects of the collision.
                col1->collisionDetected(col2);
                col2->collisionDetected(col1);
            }
        }
    }
}
