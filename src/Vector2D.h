#pragma once

#include <math.h>
#include <SDL3/SDL.h>

/// @brief Facing direction, aligns with row in character sheets
enum class DIRECTION
{
    NORTH = 3,
    EAST = 2,
    SOUTH = 0,
    WEST = 1
};

class Vector2D
{
public:
    Vector2D()
    {
        m_x = 0.0f;
        m_y = 0.0f;
    }

    Vector2D(const float x, const float y) : m_x(x), m_y(y) {}

    float getX() const { return m_x; }

    float getY() const { return m_y; }

    void setX(const float x)
    {
        m_x = x;
    }

    void setY(const float y) { m_y = y; }

    // Length
    float length() const { return sqrt(m_x * m_x + m_y * m_y); }

    // Addition
    Vector2D operator+(const Vector2D &v2) const
    {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    friend Vector2D &operator+=(Vector2D &v1, const Vector2D &v2)
    {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;
        return v1;
    }

    Vector2D operator+(const DIRECTION direction) const
    {
        switch (direction)
        {
        case DIRECTION::NORTH:
            return Vector2D(m_x, m_y - 1.0f);
        case DIRECTION::SOUTH:
            return Vector2D(m_x, m_y + 1.0f);
        case DIRECTION::WEST:
            return Vector2D(m_x - 1.0f, m_y);
        case DIRECTION::EAST:
            return Vector2D(m_x + 1.0f, m_y);
        default:
            return Vector2D(m_x, m_y);
        }
    }

    // Multiplication my a scalar
    Vector2D operator*(const float scalar) const
    {
        return Vector2D(m_x * scalar, m_y * scalar);
    }

    Vector2D &operator*=(const float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        return *this;
    }

    // Subtraction
    Vector2D operator-(const Vector2D &v2) const
    {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }

    friend Vector2D &operator-=(Vector2D &v1, const Vector2D &v2)
    {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;
        return v1;
    }

    // Division by a scalar
    Vector2D operator/(const float scalar) const
    {
        if (scalar == 0.0f)
        {
            return Vector2D(0.0f, 0.0f);
        }
        return Vector2D(m_x / scalar, m_y / scalar);
    }

    Vector2D &operator/=(const float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;
        return *this;
    }

    // Normalization
    void normalize()
    {
        const float len = length(); // Cache value
        if (len > 0)                // we never want to attempt to divide by 0
        {
            (*this) *= 1 / len;
        }
    }

    // Implicit conversion operator to SDL_FPoint
    operator SDL_FPoint() const
    {
        return SDL_FPoint{m_x, m_y};
    }

private:
    float m_x;
    float m_y;
};
