#include "../include/Player.h"
#include "../include/root.h"
#include "../include/Nodes/Sprite2D.h"

Player::Player(Vector2 position, Vector2 dim, float scale) : CharacterBody2D(position, dim, scale)
{
    visiblecollision = true;
    texture = LoadTexture("assets/coltex.png");
    std::unique_ptr<Sprite2D> sprite2d = std::make_unique<Sprite2D>("assets/player.png",dim.x, dim.y);
    Sprite2D* rawSpritePtr = sprite2d.get();
    sprite = rawSpritePtr;
    sprite2d->set_parent(this);
    addChild(std::move(sprite2d));
    root::nodes.push_back(rawSpritePtr);
}

void Player::jump()
{
    if(isOnFloor() && !jumping)
    {
        velocity.y = -15;
        jumping = true;
    }
}

void Player::update(float delta)
{
    colliding = false;
    falling = !colliding;
    if(isOnFloor())
    {
        jumping = false;
        velocity.y = 0;
    }
    handleInput();
    applyGravity(delta);
    updatePosition(delta);
    updateChildren(delta);
    updateCollisionShape2D();
}

void Player::updatePosition(float delta)
{
    direction.Normalise();

    //Move the entity
    position.x += direction.x * speed;
    position.y +=velocity.y;
    if (isOnFloor()) {
        velocity.y = 0;
        jumping = false;
    }
}

void Player::draw()
{
    if(visiblecollision)
    {
        SDL_RenderCopyEx(root::renderer, texture, &srcRect, &destRect,
                         rotation_degrees, nullptr, SDL_FLIP_NONE);
    }
    for(std::unique_ptr<Node>& node : children)
    {
        node->draw();
    }
}

void Player::applyGravity(float delta)
{
    if(falling&& ! eightway)
    {
        velocity.y += gravity;
    }
}

void Player::handleInput()
{
    direction.x = 0;
    direction.y = 0;

    if(eightway) {
        if (keystates[SDL_SCANCODE_UP]) {
            if (!keystates[SDL_SCANCODE_DOWN]) {
                direction.y = -1;
            } else {
                direction.y = 0;
            }
        }
        if (keystates[SDL_SCANCODE_LEFT]) {
            if (!keystates[SDL_SCANCODE_RIGHT]) {
                direction.x = -1;
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            } else {
                direction.x = 0;
            }
        }
        if (keystates[SDL_SCANCODE_DOWN]) {
            if (!keystates[SDL_SCANCODE_UP]) {
                direction.y = 1;
            } else {
                direction.y = 0;
            }

        }
        if (keystates[SDL_SCANCODE_RIGHT]) {
            if (!keystates[SDL_SCANCODE_LEFT]) {
                direction.x = 1;
                sprite->spriteFlip = SDL_FLIP_NONE;
            } else {
                direction.x = 0;
            }
        }
    }else
    {
        if (keystates[SDL_SCANCODE_UP])
        {
            jump();
        }
        if (keystates[SDL_SCANCODE_LEFT])
        {
            direction.x = -1;
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        }
        if (keystates[SDL_SCANCODE_RIGHT])
        {
            direction.x = 1;
            sprite->spriteFlip = SDL_FLIP_NONE;
        }
    }
}