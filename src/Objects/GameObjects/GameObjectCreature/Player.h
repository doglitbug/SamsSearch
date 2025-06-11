#pragma once

#include "Objects/GameObjects/GameObjectCreature/GameObjectCreature.h"
#include "Objects/GameObjects/GameObjectFactory.h"

class Player : public GameObjectCreature {
public:
    Player()= default;

    void load(int x, int y, int width, int height, CPO &pCustomProperties);
    void update(float deltaTime, GameObject *pPlayer = nullptr) override;
};

class PlayerCreator : public BaseCreator {
    GameObject *createGameObject() override {
        return new Player();
    }
};