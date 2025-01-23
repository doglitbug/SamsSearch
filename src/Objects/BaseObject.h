#pragma once

#include "LoaderParams.h"
#include "Vector2D.h"

/// @brief Base object for UI/Game Objects
class BaseObject {
public:
    virtual void load(const LoaderParams &pParams) = 0;

    virtual void update(float deltaTime) = 0;

    virtual void clean() = 0;

    Vector2D getPosition() { return m_position; }

protected:
    BaseObject() = default;

    ~BaseObject() = default;

    /// @brief Position on screen or in world
    Vector2D m_position;
    /// @brief Texture to draw from
    std::string m_textureID;
    /// @brief Width of object in pixels, used for drawing
    int m_width = 0;
    /// @brief Height of object in pixels, used for drawing
    int m_height = 0;
};