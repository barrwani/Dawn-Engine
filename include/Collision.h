#ifndef COLLISION_H
#define COLLISION_H

#include "SDL.h"
#include "../include/CollisionObject2D.h"

class Collision {
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const CollisionObject2D& colA, const CollisionObject2D& colB);

};

#endif //COLLISION_H
