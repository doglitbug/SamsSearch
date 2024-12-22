#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "GameObjectFactory.h"

class Player : public GameObject {
public:
    Player();

    void load(const LoaderParams *pParams) override;
    void update(float deltaTime) override;

    /// @brief
    /// @todo move back to protected/private
    float const speed = 20.0f;
};

class PlayerCreator : public BaseCreator {
    GameObject *createGameObject() override {
        return new Player();
    }
};