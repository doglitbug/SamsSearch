#include "GameObjectLayer.h"

void GameObjectLayer::update(float deltaTime, GameObject *pPlayer) {
    for (GameObject *go: m_gameObjects) {
        go->update(deltaTime, pPlayer);
    }
}

void GameObjectLayer::render(SDL_Rect *pViewPort) {
    for (GameObject *go: m_gameObjects) {
        go->drawSelf(pViewPort);
    }
}
