#include "Dog.h"

Dog::Dog() {}

void Dog::load(const LoaderParams *pParams) {
    GameObject::load(pParams);
    //TODO multiple by scale!
    m_hitBox = new SDL_FRect{6, 22, 14, 14};
}

void Dog::onInteraction(GameObject *other, INTERACT_TYPE interactType) {
    std::cout << "Bark!" << std::endl;
}
