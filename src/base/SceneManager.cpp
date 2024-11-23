#include "../../include/base/SceneManager.h"

void SceneManager::setScene(std::unique_ptr<Node> newScene) {
    if (!newScene) {
        std::cerr << "Attempted to set a nullptr scene!" << std::endl;
        return;
    }

    std::cout << "Replacing current scene..." << std::endl;
    currentScene = std::move(newScene); // Ownership is transferred, old scene is destroyed
}
void SceneManager::update(float deltaTime)
{
    currentScene->update(deltaTime);
}


void SceneManager::draw()
{
    currentScene->draw();
}

Node* SceneManager::getScene(){return currentScene.get();}