#include "GameObject.h"

void GameObject::load(int x,
                      int y,
                      int width,
                      int height,
                      CPO &pCustomProperties) {
    m_position = Vector2D(static_cast<float>(x), static_cast<float>(y));
    m_width = width;
    m_height = height;

    m_sprite = sprite{
        pCustomProperties.getString("textureID"),
        width,
        height,
        pCustomProperties.getInt("startColumn"),
        pCustomProperties.getInt("startRow")
    };

    //TODO Find or default
    m_direction = DIRECTION::SOUTH;
    m_currentFrame = 0;

    // TODO Use width and height to make a default?
    m_hitBox = nullptr;
}

void GameObject::drawSelf(SDL_Rect *pViewport) {
    //Check to see if we are off screen
    //TODO Replace with SDL_Rect intersection check?
    if ((m_position.getX() + m_width) < pViewport->x) return;
    if (m_position.getX() > (pViewport->x + pViewport->w)) return;

    if ((m_position.getY() + m_height) < pViewport->y) return;
    if (m_position.getY() > (pViewport->y + pViewport->h)) return;

    AssetManager::get()->drawSprite(m_sprite,
                                    (int) m_position.getX() - pViewport->x,
                                    (int) m_position.getY() - pViewport->y,
                                    m_direction,
                                    m_currentFrame);

    //TODO Move out of this function!
    if (SHOW_HITBOX && m_hitBox) {
        SDL_FRect hitBoxLocation;
        hitBoxLocation.x = m_position.getX() + m_hitBox->x - pViewport->x;
        hitBoxLocation.y = m_position.getY() + m_hitBox->y - pViewport->y;
        hitBoxLocation.w = m_hitBox->w;
        hitBoxLocation.h = m_hitBox->h;

        SDL_SetRenderDrawColor(EngineStateManager::get()->getRenderer(), 255, 0, 0, 0);
        SDL_RenderRect(EngineStateManager::get()->getRenderer(), &hitBoxLocation);
    }
}

void GameObject::onInteraction(GameObject *other, INTERACT_TYPE interactionType) {
    std::cout << "I was touched!" << std::endl;
}

void GameObject::clean() const {
    delete m_hitBox;
}

GameObject::~GameObject() {
    delete m_hitBox;
}

void GameObject::update(float deltaTime, GameObject *pPlayer) {
}
