#pragma once

#include <vector>

#include "Layer.h"
#include "Objects/GameObjects/GameObject.h"

class ObjectLayer : public Layer {
public:
    void update(float deltaTime) override;
    void render(SDL_Rect *pViewport) override;

    std::vector<GameObject *> *getGameObjects() {
        return &m_gameObjects;
    }

private:
    std::vector<GameObject *> m_gameObjects;
};