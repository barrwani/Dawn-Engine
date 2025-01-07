#include "../../include/base/root.h"
#include "../../include/Example/ExampleScene.h"
#include "../../include/Example/Player.h"
#include "../../include/Nodes/StaticBody2D.h"
#include <iostream>

SceneManager root::sceneManager;
// Initialize static members of the root
SDL_Renderer* root::renderer = nullptr;
Node* root::currentscene = nullptr;
SDL_Event root::event;
bool root::should_switch_scene = false; // Flag to indicate if the scene should switch
std::unique_ptr<Node> root::nextscene = nullptr;


Node* root::main_scene = nullptr; // Main Scene is the first scene to be loaded
bool root::isRunning = false; // Flag to track if the game is running

QuadTree root::colliders(0, 0, 0, 100, 100); // QuadTree for collision detection
std::vector<Node*> root::nodes; // Vector to store active nodes

SDL_Rect root::camera = { 0,0,1920,1080 }; // Camera dimensions

// Default constructor
root::root() = default;

// Default destructor
root::~root() = default;

// Initialize SDL and create window and renderer
void root::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen) // Set fullscreen flag if requested
        flags = SDL_WINDOW_FULLSCREEN;

    // Initialize SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized!..." << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags); // Create window

        if(window)
            std::cout << "Window created!" << std::endl;
        else
            std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0); // Create renderer
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set render color to white
            std::cout << "Renderer created!\n" << std::endl;
        }
        isRunning = true; // Set game running state to true
        loadScene<ExampleScene>();

    } else
        isRunning = false; // Initialization failed
}


void root::reload_current_scene() {
    Node *currentScene = sceneManager.getScene();
    if (!currentScene) {
        std::cerr << "No current scene to reload.\n"<< std::endl;
        return;
    }

    // Determine the type of the current scene and reload it
    if (dynamic_cast<ExampleScene *>(currentScene)) {
        loadScene<ExampleScene>(); // Reload ExampleScene
    }
}

void root::switchScene(std::unique_ptr<Node> newScene) {
    std::cout << "Switching scenes...\n" << std::endl;

    if (!newScene) {
        std::cerr << "Error: newScene is nullptr.\n" << std::endl;
        return;
    }

    std::cout << "New scene initialized: " << typeid(*newScene).name() << std::endl;

    // Clear current nodes before switching scenes
    nodes.clear();
    colliders.clear();

    // Set the new scene
    sceneManager.setScene(std::move(newScene));

    // Populate the nodes list with all nodes in the new scene hierarchy
    Node* currentScene = sceneManager.getScene();
    if (currentScene)
    {
        std::function<void(Node*)> collectNodes = [&](Node* node)
                {
            if (!node) return; // Ensure node is not null
            nodes.push_back(node); // Add the node to the active list
            for (Node* child : node->get_children())
            {
                if(child)
                {
                    collectNodes(child); // Recursively add children
                }
            }
        };

        collectNodes(currentScene); // Start collecting nodes from the root node
    }

    // Debug node count
    std::cout << "Nodes in new scene: " << nodes.size() << std::endl;
}


template <typename SceneType>
void root::loadScene()
{
    static_assert(std::is_base_of<Node, SceneType>::value, "SceneType must inherit from Node");
    auto newScene = std::make_unique<SceneType>();
    switchScene(std::move(newScene));
}

void root::scene(float delta)
{
    if (nextscene)
    {
        switchScene(std::move(nextscene));
        nextscene = nullptr; // Reset the next scene pointer
    }
}

// Handle SDL events
void root::handleEvents(float delta)
{
    SDL_PollEvent(&event); // Poll SDL events
    switch (event.type)
    {
        case SDL_QUIT: // Handle window close event
            isRunning = false; // Set running state to false
            break;
        default:
            break; // Ignore other events
    }
}

// Update game state and check for collisions
void root::update(float delta)
{
    colliders.checkCollisions(); // Check for collisions in the quad tree
    for(Node* node : nodes) // Update each active node
    {
        node->update(delta);
    }
}

// Render the current frame
void root::render(float delta)
{
    SDL_RenderClear(renderer); // Clear the screen
    for(Node* node : nodes) // Draw each active node
    {
        if (!node) {
            std::cerr << "Error: Null node in render!\n" << std::endl;
            continue;
        }
        node->draw();
    }
    SDL_RenderPresent(renderer); // Present the drawn frame
}

// Clean up resources on exit
void root::clean()
{
    colliders.clear(); // Clear colliders
    SDL_DestroyWindow(window); // Destroy window
    SDL_DestroyRenderer(renderer); // Destroy renderer
    SDL_Quit(); // Quit SDL subsystems
    std::cout << "Game cleaned!" << std::endl;
}

// Return the running state of the game
bool root::running() { return isRunning; }


