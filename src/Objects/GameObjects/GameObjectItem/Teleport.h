#pragma once

#include "Objects/GameObjects/GameObjectFactory.h"
#include "Objects/GameObjects/GameObject.h"
#include "GameObjectItem.h"

class Teleport : public GameObjectItem {
public:
    Teleport() = default;
    ~Teleport() = default;

    void load(int x, int y, int width, int height, CPO &pCustomProperties);
public:
    /// @brief Name of the map we are moving the player to
    std::string destMap;
    /// @brief The location to move to
    float destX;
    float destY;
    /// @brief What direction we want them to end up facing
    DIRECTION destDirection;
};

class TeleportCreator:public BaseCreator{
    GameObject* createGameObject() override {
        return new Teleport();
    }
};