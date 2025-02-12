#pragma once

#include "Objects/GameObjects/GameObjectCreature/GameObjectCreature.h"
#include "Objects/GameObjects/GameObjectFactory.h"

class Player : public GameObjectCreature {
public:
    Player();

    void load(const LoaderParams &pParams) override;
    void update(float deltaTime, GameObject *pPlayer = nullptr) override;

    /// @brief
    /// @todo move back to protected/private
    float const speed = 20.0f;
};

class PlayerCreator : public BaseCreator {
    GameObject *createGameObject() override {
        return new Player();
    }
};