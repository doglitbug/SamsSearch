#include "GameObjectLayer.h"

void GameObjectLayer::update(float deltaTime) {
    for (GameObject *go: m_gameObjects) {
        go->update(deltaTime);
    }
}

void GameObjectLayer::render(SDL_Rect *pViewPort) {
    for (GameObject *go: m_gameObjects) {
        go->drawAt(pViewPort);
    }
}
