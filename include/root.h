#ifndef ROOT_H
#define ROOT_H


#include <SDL.h>
#include "Node.h"
#include <vector>

class AssetManager;
class CollisionComponent;

//TODO: Implement scene tree
//TODO: Node_id system
class root {
public:
    root();
    ~root();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    static void handleEvents();
    static void update();
    static void render();
    void clean();
    static bool running();


    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
private:
    int cnt = 0;
    SDL_Window* window{};
};


#endif //ROOT_H
