#include "../../include/base/root.h"
#include "../../include/Nodes/CollisionObject2D.h"

CollisionObject2D::CollisionObject2D(Vector2 position, Vector2 scale)
{
    texture = LoadTexture("assets/coltex.png");
    CollisionShape2D.x = position.x;
    CollisionShape2D.y = position.y;
    CollisionShape2D.w = scale.x;
    CollisionShape2D.h = scale.y;
    //Default square for src rect
    srcRect = {0,0,32,32};
    //dest rect set to collider rect
    destRect = {CollisionShape2D.x, CollisionShape2D.y, CollisionShape2D.w, CollisionShape2D.h};
}

void CollisionObject2D::updateCollisionShape2D()
{
    destRect = CollisionShape2D;

    //updates collider rect position to match transform position
    CollisionShape2D.x = static_cast<int>(position.x);
    CollisionShape2D.y = static_cast<int>(position.y);
    CollisionShape2D.w = getWidth() * getScale();
    CollisionShape2D.h = getHeight() * getScale();

    //updates relative position to camera
    destRect.x = CollisionShape2D.x - root::camera.x;
    destRect.y = CollisionShape2D.y - root::camera.y;
}

CollisionObject2D::CollisionObject2D()
{
    texture = LoadTexture("assets/coltex.png");
    CollisionShape2D = {0,0,0,0};
    srcRect = {0,0,0,0};
    destRect = {0,0,0,0};
}
void CollisionObject2D::addCollisionLayer(int layer)
{
    if(!collisionlayers[layer])
        collisionlayers[layer] = true;
}

void CollisionObject2D::removeCollisionLayer(int layer)
{
    if(collisionlayers[layer])
        collisionlayers[layer] = false;
}

void CollisionObject2D::draw()
{
    if(visiblecollision)
    {
        SDL_RenderCopyEx(root::renderer, texture, &srcRect, &destRect,
                         rotation_degrees, nullptr, SDL_FLIP_NONE);
    }
}


bool CollisionObject2D::checkCollision(const CollisionObject2D &other)
{
    return Collision::AABB(CollisionShape2D, other.CollisionShape2D);
}


void CollisionObject2D::update(float delta)
{
    destRect = CollisionShape2D;
}



bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{
    if(recA.x + recA.w >= recB.x &&
       recB.x + recB.w >= recA.x &&
       recA.y + recA.h >= recB.y &&
       recB.y + recB.h >= recA.y)
    {
        return true;
    }
    return false;
}

SDL_Texture* CollisionObject2D::LoadTexture(const char* fileName)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);

    if(tempSurface == nullptr)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(root::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}