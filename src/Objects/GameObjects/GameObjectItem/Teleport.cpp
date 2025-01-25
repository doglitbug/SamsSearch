#include "Teleport.h"

void Teleport::load(const LoaderParams &pParams) {
    GameObject::load(pParams);
    m_hitBox =  new SDL_FRect{ 0, 0, (float)pParams.getWidth(), (float)pParams.getHeight()};
}

void Teleport::onInteraction(GameObject *other, INTERACT_TYPE interactType) {
    GameObject::onInteraction(other, interactType);
}
