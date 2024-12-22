#include "GameObject.h"

void GameObject::load(const LoaderParams *pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();

    m_textureID = pParams->getTextureID();
    m_direction = DIRECTION::SOUTH;
    m_currentFrame = 0;
    m_startColumn = pParams->getStartColumn();
    m_startRow = pParams->getStartRow();
    // TODO Use width and height to make a default?

    m_hitBox = nullptr;
}

void GameObject::drawAt(SDL_Rect *pViewport) {
    //Check to see if we are off screen
    if ((m_position.getX() + m_width) < pViewport->x) return;
    if (m_position.getX() > (pViewport->x + pViewport->w)) return;

    if ((m_position.getY() + m_height) < pViewport->y) return;
    if (m_position.getY() > (pViewport->y + pViewport->h)) return;

    AssetManager::get()->drawTextureFrame(m_textureID, (int) m_position.getX()-pViewport->x, (int) m_position.getY()-pViewport->y,
                                          m_width, m_height, m_startRow + m_direction,
                                          m_startColumn + m_currentFrame);
}

void GameObject::update(float deltaTime) {
    checkMapCollision(deltaTime);
    //checkObjectCollision(deltaTime)

}

void GameObject::faceDirection() {
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

void GameObject::onInteraction(GameObject *other, INTERACT_TYPE interactionType) {
    std::cout << "I was touched!" << std::endl;
}

void GameObject::clean() {
}

GameObject::~GameObject() {
    delete m_hitBox;
}

void GameObject::drawHitBox(SDL_Rect *pViewport) {
        //TODO VIEWPORT OFFSET
        // Draw hit box
        SDL_Rect hitBox;
        hitBox.x = m_position.getX() + m_hitBox->x;
        hitBox.y = m_position.getY() + m_hitBox->y;
        hitBox.w = m_hitBox->w;
        hitBox.h = m_hitBox->h;

        SDL_SetRenderDrawColor(EngineStateManager::get()->getRenderer(), 255, 0, 0, 0);
        SDL_RenderDrawRect(EngineStateManager::get()->getRenderer(), &hitBox);
}

void GameObject::checkMapCollision(float deltaTime) {
    Vector2D newPosition = m_position + m_velocity * deltaTime;
    if (m_pCollisionLayer && m_hitBox) {
        // Collision on X axis
        if (m_velocity.getX() < 0) {
            if (!m_pCollisionLayer->isWalkable(newPosition.getX() + m_hitBox->x, m_position.getY() + m_hitBox->y) ||
                !m_pCollisionLayer->isWalkable(newPosition.getX() + m_hitBox->x,
                                               m_position.getY() + m_hitBox->y + m_hitBox->h)) {
                m_velocity.setX(0);
            }
        } else if (m_velocity.getX() > 0) {
            if (!m_pCollisionLayer->isWalkable(newPosition.getX() + m_hitBox->x + m_hitBox->w,
                                               m_position.getY() + m_hitBox->y) ||
                !m_pCollisionLayer->isWalkable(newPosition.getX() + m_hitBox->x + m_hitBox->w,
                                               m_position.getY() + m_hitBox->y + m_hitBox->h)) {
                m_velocity.setX(0);
            }
        }

        // Collision Y axis now that X is completely clean
        if (m_velocity.getY() < 0) {
            if (!m_pCollisionLayer->isWalkable(m_position.getX() + m_hitBox->x, newPosition.getY() + m_hitBox->y) ||
                !m_pCollisionLayer->isWalkable(m_position.getX() + m_hitBox->x + m_hitBox->w,
                                               newPosition.getY() + m_hitBox->y)) {
                m_velocity.setY(0);
            }
        } else if (m_velocity.getY() > 0) {
            if (!m_pCollisionLayer->isWalkable(m_position.getX() + m_hitBox->x,
                                               newPosition.getY() + m_hitBox->y + m_hitBox->h) ||
                !m_pCollisionLayer->isWalkable(m_position.getX() + m_hitBox->x + m_hitBox->w,
                                               newPosition.getY() + m_hitBox->y + m_hitBox->h)) {
                m_velocity.setY(0);
            }
        }
    }
    m_position += m_velocity * deltaTime;

}

