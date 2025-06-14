#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "Objects/GameObjects/GameObjectFactory.h"
#include "NPC.h"

class Cat : public NPC {
public:
    Cat() = default;
    ~Cat() = default;

    void load(int x, int y, int width, int height, CPO &pCustomProperties) override;
    void onInteraction(GameObject *other, INTERACT_TYPE interactType) override;
    void update(float deltaTime, GameObject *pPlayer) override;

private:
    float m_timeBetweenMeows = 4.0f;
};

class CatCreator : public BaseCreator {
    GameObject *createGameObject() override {
        return new Cat();
    }
};
