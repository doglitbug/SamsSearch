#include "Cat.h"

void Cat::load(int x, int y, int width, int height, CPO &pCustomProperties) {
    NPC::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{12, 44, 28, 28};
    m_speed = 100.0f;
    App::get()->getAssets()->loadSound("assets/sounds/leohpaz/DomesticAnimals/Cat/Cat_Idle_Meow_1.wav", "Cat meow");
}

void Cat::onInteraction(GameObject *other, INTERACT_TYPE interactType) {
    if (timeSinceLastAction > m_timeBetweenMeows) {
        App::get()->getAssets()->playSound("Cat meow");
        timeSinceLastAction = 0.0f;
    }
}

void Cat::update(const float deltaTime, GameObject *pPlayer) {
    NPC::update(deltaTime, pPlayer);
}
