#include "Dog.h"

Dog::Dog() {}

void Dog::load(const LoaderParams &pParams) {
    NPC::load(pParams);
    //TODO multiple by scale!
    m_hitBox = new SDL_FRect{12, 44, 28, 28};
}

void Dog::onInteraction(GameObject *other, INTERACT_TYPE interactType) {
    std::cout << "Bark!" << std::endl;
}

void Dog::update(float deltaTime, GameObject *pPlayer) {
    NPC::update(deltaTime, pPlayer);
}
