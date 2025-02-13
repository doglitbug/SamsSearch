#include "Dog.h"

void Dog::load(int x, int y, int width, int height, const std::map<std::string, std::string> &pCustomProperties) {
    NPC::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{12, 44, 28, 28};
}

void Dog::onInteraction(GameObject *other, INTERACT_TYPE interactType) {
    std::cout << "Bark!" << std::endl;
}

void Dog::update(float deltaTime, GameObject *pPlayer) {
    NPC::update(deltaTime, pPlayer);
}
