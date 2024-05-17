#include "../../include/Nodes/Sprite2D.h"
#include "../../include/root.h"


Sprite2D::Sprite2D(const char* fileName)
{
    position = Vector2(0,0);
    texture = LoadTexture(fileName);
    srcRect.x = srcRect.y = 0;
    srcRect.h = 32;
    srcRect.w = 32;

}
Sprite2D::Sprite2D(const char* fileName, int w, int h)
{
    position = Vector2(0,0);
    texture = LoadTexture(fileName);
    srcRect.x = srcRect.y = 0;
    srcRect.w = w;
    srcRect.h = h;
}

Sprite2D::~Sprite2D()
{
    SDL_DestroyTexture(texture);
}

void Sprite2D::draw()
{
    if(visible)
        SDL_RenderCopyEx(root::renderer, texture, &srcRect, &destRect,
                         rotation_degrees, nullptr, spriteFlip);
}


void Sprite2D::update()
{
    parent->position = position;
    std::cout << parent->getName() << std::endl;
    position.x = static_cast<int>(position.x - root::camera.x);
    destRect.x = position.x;
    position.y = static_cast<int>(position.y - root::camera.y);
    destRect.y = position.y;
    destRect.w = getWidth() * getScale();
    destRect.h = getHeight() * getScale();
}

SDL_Texture* Sprite2D::LoadTexture(const char* fileName)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);

    if(tempSurface == nullptr)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(root::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

