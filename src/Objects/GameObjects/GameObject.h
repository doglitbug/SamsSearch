#pragma once

#include "Managers/EngineStateManager.h"
#include "Vector2D.h"
#include "CPO.h"

enum INTERACT_TYPE {
    TOUCH,
    INTERACT,
    ATTACK
};

/// @brief Object in GameWorld, Javidx9 calls this a Dynamic
class GameObject {
public:
    GameObject() = default;

    virtual ~GameObject();

    virtual void load(int x, int y, int width, int height, CPO &pCustomProperties);

    /// Draw this GameObject if visible
    /// @param pViewport World/Camera viewport
    virtual void drawSelf(SDL_Rect *pViewport);

    /// @brief
    /// @see https://youtu.be/oJvJZNyW_rw?si=05JhdC_6xejzS-5V&t=523
    /// @see https://youtu.be/oJvJZNyW_rw?si=o1UPLNghN-7xtD30&t=1702
    /// @param deltaTime
    /// @param pPlayer
    virtual void update(float deltaTime, GameObject *pPlayer = nullptr);

    /// @brief Called when another GameObject interacts with this one
    /// @param other GameObject that has interacted
    /// @param interactType Type of interaction
    virtual void onInteraction(GameObject *other, INTERACT_TYPE interactType);

    void clean() const;

    //Public because we need to both set and get these

    /// @brief World position
    Vector2D m_position;
    /// @brief Used to denote direction in sprite-sheet
    DIRECTION m_direction;

    void drawHitBox(SDL_Rect *pViewport);

    /// @brief Get hit-box in world co-ords
    /// @return
    SDL_FRect getWorldHitBox() {
        SDL_FRect hitBoxLocation;
        hitBoxLocation.x = m_position.getX() + m_hitBox->x;
        hitBoxLocation.y = m_position.getY() + m_hitBox->y;
        hitBoxLocation.w = m_hitBox->w;
        hitBoxLocation.h = m_hitBox->h;

        return hitBoxLocation;
    }

protected:
    /// @brief Objects hit-box for colliding with other objects
    SDL_FRect *m_hitBox;

    sprite m_sprite;

    /// @brief used to denote animation frame(column) in sprite-sheet
    int m_currentFrame;
    
    int m_width;
    int m_height;
};
