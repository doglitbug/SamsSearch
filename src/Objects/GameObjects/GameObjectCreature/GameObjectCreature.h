#pragma once

#include "CollisionLayer.h"
#include "Objects/GameObjects/GameObject.h"

/// @brief A GameObject that thinks, moves and acts
class GameObjectCreature : public GameObject {
public:

    /// @brief Choose a direction to face based on movement vector
    void faceDirection();

    /// @brief Velocity
    Vector2D m_velocity;

    /// @brief Current speed
    float m_speed;

    /// @brief Used for next think (so we are not thinking 60 times a second
    float timeElapsed;

    void checkMapCollision(float deltaTime, const CollisionLayer &m_pCollisionLayer);
};
