#include "Player.h"
#include "Managers/InputManager.h"

void Player::load(int x, int y, int width, int height, const std::map<std::string, std::string> &pCustomProperties) {
    GameObjectCreature::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{12, 44, 28, 28};
}

void Player::update(float deltaTime, GameObject *pPlayer)
{
    int frames[] = {0, 1, 2, 1};

    m_currentFrame = frames[int((SDL_GetTicks() / 150) % sizeof(frames) / sizeof(frames[0]))];

    faceDirection();
}
