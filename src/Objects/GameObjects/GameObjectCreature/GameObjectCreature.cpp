#include "GameObjectCreature.h"

void GameObjectCreature::faceDirection() {
    if (m_velocity.getX() < 0) {
        m_direction = DIRECTION::WEST;
    } else if (m_velocity.getX() > 0) {
        m_direction = DIRECTION::EAST;
    } else if (m_velocity.getY() < 0) {
        m_direction = DIRECTION::NORTH;
    } else if (m_velocity.getY() > 0) {
        m_direction = DIRECTION::SOUTH;
    } else {
        // No movement whatsoever, so stop animation
        m_currentFrame = 1;
        //m_direction = DIRECTION::SOUTH;
    }
}

void GameObjectCreature::checkMapCollision(float deltaTime, CollisionLayer m_pCollisionLayer) {
    Vector2D newPosition = m_position + m_velocity * deltaTime;
        // Collision on X axis
        if (m_velocity.getX() < 0) {
            if (!m_pCollisionLayer.isWalkable(newPosition.getX() + m_hitBox->x, m_position.getY() + m_hitBox->y) ||
                !m_pCollisionLayer.isWalkable(newPosition.getX() + m_hitBox->x,
                                               m_position.getY() + m_hitBox->y + m_hitBox->h)) {
                m_velocity.setX(0);
            }
        } else if (m_velocity.getX() > 0) {
            if (!m_pCollisionLayer.isWalkable(newPosition.getX() + m_hitBox->x + m_hitBox->w,
                                               m_position.getY() + m_hitBox->y) ||
                !m_pCollisionLayer.isWalkable(newPosition.getX() + m_hitBox->x + m_hitBox->w,
                                               m_position.getY() + m_hitBox->y + m_hitBox->h)) {
                m_velocity.setX(0);
            }
        }

        // Collision Y axis now that X is completely clean
        if (m_velocity.getY() < 0) {
            if (!m_pCollisionLayer.isWalkable(m_position.getX() + m_hitBox->x, newPosition.getY() + m_hitBox->y) ||
                !m_pCollisionLayer.isWalkable(m_position.getX() + m_hitBox->x + m_hitBox->w,
                                               newPosition.getY() + m_hitBox->y)) {
                m_velocity.setY(0);
            }
        } else if (m_velocity.getY() > 0) {
            if (!m_pCollisionLayer.isWalkable(m_position.getX() + m_hitBox->x,
                                               newPosition.getY() + m_hitBox->y + m_hitBox->h) ||
                !m_pCollisionLayer.isWalkable(m_position.getX() + m_hitBox->x + m_hitBox->w,
                                               newPosition.getY() + m_hitBox->y + m_hitBox->h)) {
                m_velocity.setY(0);
            }
        }

    m_position += m_velocity * deltaTime;
}