#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "GameObjectFactory.h"

class Teleport : public GameObject {
public:
    Teleport() = default;
    ~Teleport() = default;

    void load(const LoaderParams *pParams) override;
    void update(float deltaTime) override;

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