#pragma once

#include "Objects/GameObjects/GameObjectFactory.h"
#include "Objects/GameObjects/GameObject.h"
#include "GameObjectItem.h"

class Sign final : public GameObjectItem {
public:
    Sign() = default;
    ~Sign() = default;

    void load(int x, int y, int width, int height, CPO &pCustomProperties) override;

    /// Draw nothing
    void drawSelf(SDL_Rect *pViewport) override {};

    /// @brief Text written on the sign
    std::vector<std::string> text;
};

class SignCreator:public BaseCreator{
    GameObject* createGameObject() override {
        return new Sign();
    }
};