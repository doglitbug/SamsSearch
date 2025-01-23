#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "Objects/GameObjects/GameObjectFactory.h"
#include "GameObjectItem.h"

class Teleport : public GameObjectItem {
public:
    Teleport() = default;
    ~Teleport() = default;

    void load(const LoaderParams &pParams) override;
    void onInteraction(GameObject* other, INTERACT_TYPE interactType) override;

private:
    std::string destMap;
    Vector2D destLocation;
    DIRECTION destDirection;

};

class TeleportCreator:public BaseCreator{
    GameObject* createGameObject() override {
        return new Teleport();
    }
};