#ifndef PLAYER_H
#define PLAYER_H
#include "Nodes/CharacterBody2D.h"
class Sprite2D;

class Player : public CharacterBody2D {
public:
    Player(Vector2 position, Vector2 dim, float scale) ;
    ~Player() override= default;
    void handleInput();
    void applyGravity(float delta);
    void updatePosition(float delta);
    void update(float delta) override;
    void jump();
    int gravity = 5;
    bool falling;
    bool eightway = false;
    bool jumping;
    std::string type = "CharacterBody2D";
    void draw() override;
private:
    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    Sprite2D* sprite;
};


#endif //PLAYER_H
