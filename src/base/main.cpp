#include <SDL.h>
#include <vector>
#include "../../include/base/root.h"


root* rootscene = nullptr;

int main(int argc, char* argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    rootscene = new root();

    rootscene->init("Dawn Engine", SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED, 1024, 600, false);

    float delta = 0.0f;
    while(root::running())
    {
        frameStart = SDL_GetTicks();
        root::handleEvents(delta);
        root::update(delta);
        root::render(delta);
        root::scene(delta);

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        delta = frameTime / 1000.0f;
    }
    rootscene->clean();
    return 0;


}