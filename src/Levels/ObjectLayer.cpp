#include "ObjectLayer.h"

void ObjectLayer::update(float deltaTime) {
    for (GameObject *go: m_gameObjects) {
        go->update(deltaTime);
    }
}

void ObjectLayer::render(SDL_Rect *pViewPort) {
    for (GameObject *go: m_gameObjects) {
        go->drawAt(pViewPort);
    }
}
