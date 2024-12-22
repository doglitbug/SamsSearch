#pragma once

#include "BaseObject.h"
#include "Managers/AssetManager.h"
#include "Managers/EngineStateManager.h"
#include "Vector2D.h"
#include "Levels/CollisionLayer.h"

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

    void load(const LoaderParams *pParams) override;
    void drawAt(SDL_Rect *pViewPort);

    /// @brief
    /// @see https://youtu.be/oJvJZNyW_rw?si=05JhdC_6xejzS-5V&t=523
    /// @see https://youtu.be/oJvJZNyW_rw?si=o1UPLNghN-7xtD30&t=1702
    /// @param deltaTime
    void update(float deltaTime) override;

    /// @brief Choose a direction to face based on movement vector
    void faceDirection();

    /// @brief Called when another GameObject interacts with this one
    /// @param other GameObject that has interacted
    void onInteraction(GameObject* other, INTERACT_TYPE interactType);

    void clean() override;

    /// @brief Set this objects collision layer
    /// @param pCollisionLayer
    void setCollisionLayer(CollisionLayer *pCollisionLayer) {
        m_pCollisionLayer = pCollisionLayer;
    }

    /// @brief GameObject velocity
    /// @todo Move this back to protected/private
    Vector2D m_velocity;

protected:

    /// @brief Used to denote direction in sprite-sheet
    DIRECTION m_direction;
    /// @brief used to denote animation frame(column) in sprite-sheet
    int m_currentFrame;

    int m_startColumn;
    int m_startRow;

    /// @brief Collision layer for moving around world
    CollisionLayer *m_pCollisionLayer;
    /// @brief Objects hit-box for colliding with other objects
    SDL_Rect *m_hitBox;

private:
    void drawHitBox(SDL_Rect *pViewport);
    void checkMapCollision(float deltaTime);
};