
#ifndef SPRITE2D_H
#define SPRITE2D_H
#include "Node2D.h"
#include "SDL_image.h"
#include <map>

struct Animation{

    int index;
    int speed;
    int frames;

    Animation() {}
    Animation(int i, int s, int f) {index = i; speed = s; frames = f; }
};

class Sprite2D : public Node2D{
public:
    //Constructors, Destructor
    explicit Sprite2D(const char* fileName);
    Sprite2D(const char* fileName, int w, int h);
    ~Sprite2D();
    static SDL_Texture* LoadTexture(const char* fileName);

    std::map<const char*, Animation> animations;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    void update() override;
    void draw() override;
    int currentFrame = 0;


protected:
    SDL_Texture* texture{};
    SDL_Rect srcRect{}, destRect{};
    const char* src;
    bool visible = true;

};


#endif //SPRITE2D_H
