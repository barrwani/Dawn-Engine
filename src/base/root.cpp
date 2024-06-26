#include "../../include/base/root.h"
#include "../../include/Example/Player.h"
#include "../../include/Nodes/StaticBody2D.h"
#include <iostream>


SDL_Renderer* root::renderer = nullptr;
SDL_Event root::event;

int prevscene;
bool root::justEntered = true;
int root::currentstate = level1;

bool root::isRunning = false;

QuadTree root::colliders(0, 0, 0, 100, 100);
std::vector<Node*> root::nodes;
std::vector<std::unique_ptr<Node>> root::children;

SDL_Rect root::camera = { 0,0,1920,1080 };

root::root()
= default;
root::~root()
= default;

void root::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized!..." << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(window)
            std::cout << "Window created!" << std::endl;
        else
            std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;

    } else
        isRunning = false;

}

void root::scene(float delta)
{
    if(currentstate!= prevscene){justEntered = true;}
    switch(currentstate)
    {
        case level1:
            if(justEntered)
            {
                justEntered = false;
                std::unique_ptr<Player> player = std::make_unique<Player>(Vector2(400.0f,400.0f), Vector2(32.0f,32.0f),1.0f);
                nodes.push_back(player.get());
                for(auto& child : player->children)
                {
                    nodes.push_back(child.get());
                }
                addChild(std::move(player));


                std::unique_ptr<StaticBody2D> wall = std::make_unique<StaticBody2D>(Vector2(200.0f,500.0f), Vector2(500.0f,20.0f), 1.0f);
                nodes.push_back(wall.get());
                addChild(std::move(wall));
            }
            prevscene = level1;

    }
}

void root::handleEvents(float delta)
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void root::update(float delta)
{
    colliders.checkCollisions();
    for(Node* node : nodes)
    {
        node->update(delta);
    }
}



void root::render(float delta)
{
    SDL_RenderClear(renderer);
    for(Node* node : nodes)
    {
        node->draw();
    }
    SDL_RenderPresent(renderer);

}


void root::clean()
{
    colliders.clear();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
bool root::running() {return isRunning;}


