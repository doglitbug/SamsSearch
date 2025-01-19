#include "Button.h"
#include "../../Managers/InputManager.h"

void Button::load(const LoaderParams &pParams) {
    UIObject::load(pParams);
    m_currentFrame = INACTIVE;
    m_bReleased = false;
}

void Button::update(float deltaTime) {
    Vector2D *pMousePos = InputManager::get()->getMousePosition();

    // Check if mouse is hovering over button
    // TODO Replace with SDL_PointInRect?
    if (pMousePos->getX() < (m_position.getX() + m_width)
        && pMousePos->getX() > m_position.getX()
        && pMousePos->getY() < (m_position.getY() + m_height)
        && pMousePos->getY() > m_position.getY()) {

        if (InputManager::get()->getMouseButtonState(InputManager::get()->LEFT) && m_bReleased) {
            m_bReleased = false;
            m_callback();
        } else if (!InputManager::get()->getMouseButtonState(InputManager::get()->LEFT)) {
            m_bReleased = true;
            m_currentFrame = ACTIVE;
        }
    } else {
        m_currentFrame = INACTIVE;
    }
}