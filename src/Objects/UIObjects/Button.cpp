#include "Button.h"
#include "App.h"

void Button::load(const LoaderParams &pParams) {
    UIObject::load(pParams);
    m_currentFrame = INACTIVE;
    m_bReleased = false;
}

void Button::update(float deltaTime) {
    Vector2D *pMousePos = App::get()->getInput()->getMousePosition();

    // Check if mouse is hovering over button
    // TODO Replace with SDL_PointInRect?
    if (pMousePos->getX() < (m_ScreenPosition.getX() + m_width)
        && pMousePos->getX() > m_ScreenPosition.getX()
        && pMousePos->getY() < (m_ScreenPosition.getY() + m_height)
        && pMousePos->getY() > m_ScreenPosition.getY()) {

        if (App::get()->getInput()->getMouseButtonState(InputSystem::LEFT) && m_bReleased) {
            m_bReleased = false;
            m_callback();
        } else if (!App::get()->getInput()->getMouseButtonState(InputSystem::LEFT)) {
            m_bReleased = true;
            m_currentFrame = ACTIVE;
        }
    } else {
        m_currentFrame = INACTIVE;
    }
}