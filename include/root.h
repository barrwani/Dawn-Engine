#ifndef ROOT_H
#define ROOT_H


#include <SDL.h>
#include "Nodes/Node.h"
#include <vector>
#include "QuadTree.h"
#include <unordered_set>


class Node;
class Player;
class root {
public:
    root();

    ~root();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    static void handleEvents(float delta);

    static void update(float delta);

    static void render(float delta);

    static void scene(float delta);

    void clean();

    static void addChild(std::unique_ptr<Node> child) {children.push_back(std::move(child));}

    static bool running();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static bool justEntered;
    static SDL_Rect camera;
    static std::vector<Node*> nodes;
    static QuadTree colliders;
    static std::vector<std::unique_ptr<Node>> children;
    enum gameState{
    menu,
    level1,
    //etc
    };
    static int currentstate;


private:
    int cnt = 0;
    SDL_Window* window{};


};


#endif //ROOT_H
