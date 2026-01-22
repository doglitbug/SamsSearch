#include "Dog.h"

void Dog::load(int x, int y, int width, int height, CPO &pCustomProperties) {
    NPC::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{12, 44, 28, 28};
    m_speed = 100.0f;
    Assets::get()->loadSound("assets/sounds/leohpaz/DomesticAnimals/Dog/Dog_Bark_1.wav", "Dog bark");
}

void Dog::onInteraction(GameObject *other, INTERACT_TYPE interactType) {
    if (timeSinceLastAction > m_timeBetweenBarks) {
        Assets::get()->playSound("Dog bark");
        timeSinceLastAction = 0.0f;
    }
}

void Dog::update(const float deltaTime, GameObject *pPlayer) {
    NPC::update(deltaTime, pPlayer);
}
