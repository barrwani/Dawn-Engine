#ifndef ROOT_H
#define ROOT_H


#include <SDL.h>
#include "Nodes/Node.h"
#include <vector>
#include "QuadTree.h"
#include <unordered_set>

//TODO: Implement scene tree
//TODO: Node_id system
class Node;
class root {
public:
    root();

    ~root();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    static void handleEvents();

    static void update();

    static void render();

    void clean();

    static bool running();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static std::vector<Node*> nodes;
    int currentstate;
    static QuadTree colliders;
    static std::unordered_set<std::unique_ptr<Node>> children;
    enum gameState{
    menu,
    level1,
    //etc
    };

private:
    int cnt = 0;
    SDL_Window* window{};


};


#endif //ROOT_H
