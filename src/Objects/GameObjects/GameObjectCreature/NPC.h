#pragma once

#include "Objects/GameObjects/GameObjectCreature/GameObjectCreature.h"
#include "Objects/GameObjects/GameObjectFactory.h"

class NPC : public GameObjectCreature {
public:
    NPC();

    void load(const LoaderParams &pParams) override;
    void update(float deltaTime) override;
private:
    //Various default behaviours to be placed here
    Vector2D chooseRandomDirection();
    float timeElapsed;
};

class NPCCreator:public BaseCreator{
    GameObject* createGameObject() override {
        return new NPC();
    }
};