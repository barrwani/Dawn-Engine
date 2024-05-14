#include "../include/root.h"
#include <iostream>
#include "../include/Collision.h"


SDL_Renderer* root::renderer = nullptr;
SDL_Event root::event;

bool root::isRunning = false;

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

void root::handleEvents()
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

void root::update()
{

}



void root::render()
{
    SDL_RenderClear(renderer);




    SDL_RenderPresent(renderer);

}


void root::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
bool root::running() {return isRunning;}


