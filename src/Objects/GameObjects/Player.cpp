#include "Player.h"
#include "Managers/InputManager.h"

Player::Player() {}

void Player::load(const LoaderParams *pParams)
{
    GameObject::load(pParams);
    m_hitBox = new SDL_Rect {12, 44, 28, 28};
}

void Player::update(float deltaTime)
{
    int frames[] = {0, 1, 2, 1};

    m_currentFrame = frames[int((SDL_GetTicks() / 150) % 4)];

    GameObject::update(deltaTime);

    faceDirection();
}
