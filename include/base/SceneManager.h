#ifndef DAWN_ENGINE_SCENEMANAGER_H
#define DAWN_ENGINE_SCENEMANAGER_H
#include <memory>
#include "../Nodes/Node.h"

class SceneManager {

private:
    std::unique_ptr<Node> currentScene;

public:
    SceneManager() = default;
    ~SceneManager() = default;

    Node* getCurrentScene(){return currentScene.get();}


    void setScene(std::unique_ptr<Node> newScene);

    Node* getScene();

    void update(float deltaTime);
    void draw();
};


#endif //DAWN_ENGINE_SCENEMANAGER_H
