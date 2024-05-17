#ifndef COLLISIONOBJECT2D_H
#define COLLISIONOBJECT2D_H

#include "Node2D.h"
#include "SDL_image.h"
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

    void updateCollisionShape2D();

    SDL_Texture* LoadTexture(const char* fileName);

    SDL_Rect getCollider() const {return CollisionShape2D;}
    virtual void collisionDetected(CollisionObject2D* col) = 0;
    bool checkCollision(const CollisionObject2D& other);

    double getLeft() const { return position.x; }
    double getRight() const { return position.x + dim.x; }
    double getTop() const { return position.y; }
    double getBottom() const { return position.y + dim.y; }

    void moveX(double dx) { position.x += dx; }
    void moveY(double dy) { position.y += dy; }

    void addCollisionLayer(int layer);
    void removeCollisionLayer(int layer);

    int getType()  const {return type;}

    int getWidth() const override {return CollisionShape2D.w;}
    int getHeight() const override {return CollisionShape2D.h;}


    SDL_Rect CollisionShape2D;
    bool collision = true;



protected:
    //0 is static, 1 is area, 2 is character
    int type;
    SDL_Rect srcRect, destRect;
    std::map<int,bool> collisionlayers;
    bool visiblecollision = false;
    SDL_Texture* texture;
};


#endif //COLLISIONOBJECT2D_H
