#pragma once

#include "BaseObject.h"
#include "Managers/AssetManager.h"
#include "Managers/EngineStateManager.h"
#include "Vector2D.h"
#include "Maps/CollisionLayer.h"

enum INTERACT_TYPE {
    //Walked or collided with each other
    TOUCH,
    //Deliberate interaction eg used action button
    INTERACT
};

/// @brief BaseObject in GameWorld
class GameObject : public BaseObject {
public:
    GameObject() = default;
    ~GameObject();

    void load(const LoaderParams &pParams) override;
    void drawAt(SDL_Rect *pViewPort);

    /// @brief
    /// @see https://youtu.be/oJvJZNyW_rw?si=05JhdC_6xejzS-5V&t=523
    /// @see https://youtu.be/oJvJZNyW_rw?si=o1UPLNghN-7xtD30&t=1702
    /// @param deltaTime
    void update(float deltaTime) override;

    /// @brief Called when another GameObject interacts with this one
    /// @param other GameObject that has interacted
    /// @param interactType Type of interaction
    virtual void onInteraction(GameObject* other, INTERACT_TYPE interactType);

    void clean() override;

    void drawHitBox(SDL_Rect *pViewport);

    /// @brief Objects hit-box for colliding with other objects
    SDL_FRect *m_hitBox;

    SDL_FRect *getWorldHitBox(){
        if(!m_hitBox) return nullptr;
        SDL_FRect *hitBoxLocation = new SDL_FRect();
        hitBoxLocation->x = m_position.getX() + m_hitBox->x;
        hitBoxLocation->y = m_position.getY() + m_hitBox->y ;
        hitBoxLocation->w = m_hitBox->w;
        hitBoxLocation->h = m_hitBox->h;

        return hitBoxLocation;
    }

protected:
    /// @brief Used to denote direction in sprite-sheet
    DIRECTION m_direction;
    /// @brief used to denote animation frame(column) in sprite-sheet
    int m_currentFrame;

    int m_startColumn;
    int m_startRow;
};