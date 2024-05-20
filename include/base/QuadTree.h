#ifndef QUADTREE_H
#define QUADTREE_H
#include "../Nodes/CollisionObject2D.h"

class CollisionObject2D;
class QuadTree {
public:
    QuadTree(int level, int x, int y, int w, int h);
    void clear();
    void insert(CollisionObject2D* collision_node);
    void checkCollisions();
    void retrieve(std::vector<CollisionObject2D*>& returnCols, CollisionObject2D* collision_node);
    void remove(CollisionObject2D* collision_node);
private:
    int level;
    int x,y,w,h;
    std::vector<CollisionObject2D*> collision_nodes;
    std::vector<std::unique_ptr<QuadTree>> nodes;

    void split();
    int getIndex(CollisionObject2D* collision_node);
    const int MAX_COL_NODES = 10;
    const int MAX_LEVELS = 5;
};


#endif //QUADTREE_H
