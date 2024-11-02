#include "../../include/base/root.h"
#include "../../include/Example/Player.h"
#include "../../include/Nodes/StaticBody2D.h"
#include <iostream>

// Initialize static members of the root class
SDL_Renderer* root::renderer = nullptr;
SDL_Event root::event;
bool root::scene_initialized = false;
bool root::should_switch_scene = false; // Flag to indicate if the scene should switch

bool root::justEntered = true; // Flag to track if the scene is newly entered
std::unique_ptr<Node> root::currentscene = nullptr; // Pointer to the current scene
std::unique_ptr<Node>  root::main_scene = nullptr; // Pointer to the main scene
bool root::isRunning = false; // Flag to track if the game is running

QuadTree root::colliders(0, 0, 0, 100, 100); // QuadTree for collision detection
std::vector<Node*> root::nodes; // Vector to store active nodes
std::vector<std::unique_ptr<Node>> root::children; // Vector to store unique child nodes

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
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true; // Set game running state to true
        main_scene = std::make_unique<Player>(Vector2(400.0f,400.0f),
                                              Vector2(32.0f,32.0f),
                                              1.0f);

    } else
        isRunning = false; // Initialization failed
}

void root::switch_scene(std::unique_ptr<Node> newscene)
{
    should_switch_scene = true;      // Set flag to switch scenes

    nodes.clear();       // Clear active nodes
    colliders.clear();   // Clear colliders
    children.clear();    // Clear children

    currentscene = std::move(newscene);  // Set current scene to the new scene using move semantics
}

void root::reload_current_scene()
{
    switch_scene(std::move(currentscene));  // Move current scene back to itself to trigger reload
}

// Handle scene initialization
//TODO: Rethink logic with main_scene, current_scene, etc..
void root::scene(float delta)
{
    if (justEntered || !currentscene || should_switch_scene)
    {
        if (!scene_initialized)
        {
            if (!currentscene)
            {
                currentscene = std::move(main_scene); // Move main scene to current scene
            }
            nodes.push_back(currentscene.get());
            for (auto &child : currentscene->children)
            {
                nodes.push_back(child.get());
            }
            children.push_back(std::move(currentscene)); // Only move once
            scene_initialized = true;  // Mark as initialized
        }
        justEntered = false;
        should_switch_scene = false;
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
