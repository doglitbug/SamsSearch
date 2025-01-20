#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "GameObjectFactory.h"

class Teleport : public GameObject {
public:
    Teleport() = default;
    ~Teleport() = default;

    void load(const LoaderParams &pParams) override;
    void update(float deltaTime) override;
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