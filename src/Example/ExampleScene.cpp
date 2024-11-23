
#include "../../include/Example/ExampleScene.h"
#include "../../include/Example/Player.h"
#include "../../include/base/root.h"
#include "../../include/Nodes/Sprite2D.h"
#include "../../include/Nodes/StaticBody2D.h"

ExampleScene::ExampleScene() : Node2D(Vector2(0, 0), Vector2(1280, 600), 1.0f)
{
    setName("ExampleScene");

    // Create and add the player
    auto player = std::make_unique<Player>(Vector2(400.0f, 400.0f),
                                           Vector2(32.0f, 32.0f),
                                           1.0f);
    player->set_parent(this);
    addChild(std::move(player));

    // Add static bodies
    addChild(std::make_unique<StaticBody2D>(Vector2(0, 0), Vector2(1280, 32), 2.0f));
    addChild(std::make_unique<StaticBody2D>(Vector2(0, 0), Vector2(32, 600), 2.0f));
    addChild(std::make_unique<StaticBody2D>(Vector2(0, 550), Vector2(1280, 32), 2.0f));
    addChild(std::make_unique<StaticBody2D>(Vector2(1000, 0), Vector2(32, 600), 2.0f));
}


