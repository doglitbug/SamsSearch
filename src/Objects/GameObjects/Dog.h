#pragma once

#include "Objects/GameObjects/GameObject.h"
#include "GameObjectFactory.h"
#include "NPC.h"

class Dog : public GameObject {
public:
    Dog();
    void load(const LoaderParams &pParams) override;
    /// @brief Called when another GameObject interacts with this one
    /// @param other GameObject that has interacted
    void onInteraction(GameObject* other, INTERACT_TYPE interactType) override;
};

class DogCreator : public BaseCreator {
    GameObject *createGameObject() override {
        return new Dog();
    }
};