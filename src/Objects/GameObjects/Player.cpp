#include "Player.h"
#include "Managers/InputManager.h"

Player::Player() {}

void Player::load(const LoaderParams &pParams)
{
    GameObject::load(pParams);
    //TODO multiple by scale!
    m_hitBox = new SDL_FRect{6, 22, 14, 14};
}

void Player::update(float deltaTime)
{
    int frames[] = {0, 1, 2, 1};

    m_currentFrame = frames[int((SDL_GetTicks() / 150) % sizeof(frames) / sizeof(frames[0]))];

    GameObject::update(deltaTime);

    faceDirection();
}
