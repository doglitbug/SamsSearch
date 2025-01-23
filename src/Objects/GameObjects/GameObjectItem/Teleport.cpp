#include "Teleport.h"

void Teleport::load(const LoaderParams &pParams) {
    GameObject::load(pParams);
}

void Teleport::onInteraction(GameObject *other, INTERACT_TYPE interactType) {
    GameObject::onInteraction(other, interactType);
}
