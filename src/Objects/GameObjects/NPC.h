#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "GameObjectFactory.h"

class NPC : public GameObject {
public:
    NPC();

    void load(const LoaderParams *pParams) override;
    void update(float deltaTime) override;
private:
    Vector2D chooseRandomDirection();
    float timeElapsed;
};

class NPCCreator:public BaseCreator{
    GameObject* createGameObject() override {
        return new NPC();
    }
};