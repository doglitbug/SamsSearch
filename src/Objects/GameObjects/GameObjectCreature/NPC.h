#pragma once

#include "Objects/GameObjects/GameObjectCreature/GameObjectCreature.h"
#include "Objects/GameObjects/GameObjectFactory.h"

class NPC : public GameObjectCreature {
public:
    NPC() = default;
    ~NPC() = default;


    void load(int x, int y, int width, int height, CPO &pCustomProperties) override;
    void update(float deltaTime, GameObject *pPlayer) override;

private:
    //Various default behaviours to be placed here
    static Vector2D chooseRandomDirection();
};