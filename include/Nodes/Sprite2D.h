
#ifndef SPRITE2D_H
#define SPRITE2D_H
#include "Node2D.h"

//TODO: Set up SDL_Image, image transformations
class Sprite2D : public Node2D{
public:
    Sprite2D();
    ~Sprite2D();
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
private:
    const char* src;
    bool visible;
    bool flip_h;
    bool flip_v;


};


#endif //SPRITE2D_H
