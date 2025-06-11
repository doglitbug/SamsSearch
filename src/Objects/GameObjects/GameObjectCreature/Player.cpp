#include "Player.h"
#include "Managers/InputManager.h"

void Player::load(const int x, const int y, const int width, const int height, CPO &pCustomProperties) {
    GameObjectCreature::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{12, 44, 28, 28};
    m_speed = 150.0f;
    AssetManager::get()->loadSound("assets/sounds/chiptunes/action-and-game/NFF-quick-move.wav", "Enter door");
    AssetManager::get()->loadSound("assets/sounds/chiptunes/fantasy-and-magic/NFF-finger-snap.wav", "Footstep");
    AssetManager::get()->loadSound("assets/sounds/chiptunes/fantasy-and-magic/NFF-finger-snap-02.wav", "Footstep2");
}

void Player::update(const float deltaTime, GameObject *pPlayer)
{
    constexpr int frames[] = {0, 1, 2, 1};
    m_currentFrame = frames[static_cast<int>((SDL_GetTicks() / 25) % sizeof(frames) / sizeof(frames[0]))];

    faceDirection();

    timeElapsed += deltaTime;

    //TODO Check for running?
    //TODO Add sneakers as an item to remove this annoying sound
    if (m_velocity.length() > 0.5f & timeElapsed > 0.25f) {
        if (random() % 10 > 8) {
            AssetManager::get()->playSound("Footstep");
        } else {
            AssetManager::get()->playSound("Footstep2");
        }
        timeElapsed = 0.0f;
    }
}
