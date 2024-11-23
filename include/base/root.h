#ifndef ROOT_H
#define ROOT_H


#include <SDL.h>
#include "../Nodes/Node.h"
#include <vector>
#include "QuadTree.h"
#include <unordered_set>
#include "SceneManager.h"


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


    static bool running();

    static Node* currentscene;
    static SceneManager sceneManager;
    static void switch_scene(std::unique_ptr<Node> newscene);
    static void reload_current_scene();
    static bool should_switch_scene;
    static Node* get_current_scene() {return currentscene;}
    static Node* main_scene;
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static bool justEntered;
    static SDL_Rect camera;
    static std::vector<Node*> nodes;
    static QuadTree colliders;
    static std::unique_ptr<Node> nextscene;
    // Scene Management
    template <typename SceneType>
    static void loadScene();

    static void switchScene(std::unique_ptr<Node> newScene);

private:
    int cnt = 0;
    SDL_Window* window{};


};


#endif //ROOT_H
