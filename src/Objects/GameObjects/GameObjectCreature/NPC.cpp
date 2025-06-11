#include "NPC.h"

void NPC::load(const int x, const int y, const int width, const int height, CPO &pCustomProperties) {
    GameObjectCreature::load(x, y, width, height, pCustomProperties);

    timeElapsed = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (8)));
    timeSinceLastAction = 10.0f; //Set to 10 so we can have an instant bark on first touch
}

void NPC::update(const float deltaTime, GameObject *pPlayer) {
    constexpr int frames[] = {0, 1, 2, 1};
    m_currentFrame = frames[static_cast<int>((SDL_GetTicks() / 150) % 4)];

    timeElapsed += deltaTime;
    timeSinceLastAction += deltaTime;

    if (timeElapsed > 5.0f) {
        m_velocity = chooseRandomDirection();
        timeElapsed = 0.0f;
    }

    faceDirection();
}

Vector2D NPC::chooseRandomDirection() const {
    const float x = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2)));
    const float y = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2)));

    auto direction = Vector2D(x, y);

    direction.normalize();
    direction *= m_speed;

    return direction;
}
