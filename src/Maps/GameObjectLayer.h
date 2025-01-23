#pragma once

#include <vector>

#include "BaseLayer.h"
#include "Objects/GameObjects/GameObject.h"

class GameObjectLayer : public BaseLayer {
public:
    void update(float deltaTime) override;
    void render(SDL_Rect *pViewport) override;

    std::vector<GameObject *> *getGameObjects() {
        return &m_gameObjects;
    }

private:
    std::vector<GameObject *> m_gameObjects;
};