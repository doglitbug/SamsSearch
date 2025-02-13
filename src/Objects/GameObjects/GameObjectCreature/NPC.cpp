#include "NPC.h"

void NPC::load(const LoaderParams &pParams) {
    GameObject::load(pParams);
    //m_hitBox = new SDL_Rect{12, 44, 28, 28};
    timeElapsed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (8)));
}

void NPC::update(float deltaTime, GameObject *pPlayer) {
    int frames[] = {0, 1, 2, 1};
    m_currentFrame = frames[int((SDL_GetTicks() / 150) % 4)];

    timeElapsed += deltaTime;
    if (timeElapsed > 8.5f) {
        m_velocity = chooseRandomDirection();
        timeElapsed = 0.0f;
    }

    faceDirection();
}

Vector2D NPC::chooseRandomDirection() {

    float x, y;
    x = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2)));
    y = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2)));

    auto direction = Vector2D(x, y);

    direction.normalize();
    direction *= 10.0f;

    return direction;
}