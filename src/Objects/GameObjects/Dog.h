#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "GameObjectFactory.h"
#include "NPC.h"

class Dog : public NPC {
public:
    Dog();
    void load(const LoaderParams &pParams) override;

    void onInteraction(GameObject* other, INTERACT_TYPE interactType) override;

    void update(float deltaTime) override;
};

class DogCreator : public BaseCreator {
    GameObject *createGameObject() override {
        return new Dog();
    }
};