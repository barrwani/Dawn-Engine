#ifndef COLLISIONOBJECT2D_H
#define COLLISIONOBJECT2D_H

#include "Node2D.h"
#include <map>

struct Collision {
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};

class CollisionObject2D : public Node2D {
public:
    CollisionObject2D();
    CollisionObject2D(Vector2 position, Vector2 scale);
    virtual void update() override;
    virtual void draw() override;

    SDL_Rect getCollider() const {return CollisionShape2D;}
    virtual void collisionDetected(CollisionObject2D* col) = 0;
    bool checkCollision(const CollisionObject2D& other);

    void addCollisionLayer(int layer);
    void removeCollisionLayer(int layer);

    int getWidth() const override {return CollisionShape2D.w;}
    int getHeight() const override {return CollisionShape2D.h;}

    std::string type;
    SDL_Rect CollisionShape2D;
    bool collision = true;



protected:
    SDL_Rect srcRect, destRect;
    std::map<int,bool> collisionlayers;
    bool visiblecollision = false;
    SDL_Texture* texture;
};


#endif //COLLISIONOBJECT2D_H
