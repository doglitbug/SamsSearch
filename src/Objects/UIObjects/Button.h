#pragma once

#include <functional>
#include <utility>
#include "UIObject.h"

/// @brief Create a clickable button
class Button : public UIObject
{
public:
    void load(const LoaderParams& pParams) override;
    void update(float deltaTime) override;

    void setCallback(const std::function<void()>& callback) { m_callback = callback; }

private:
    enum class buttonState
    {
        INACTIVE = 0,
        ACTIVE = 1,
        SELECTED = 2,
    };

    bool m_bReleased = false;
    int m_currentFrame = static_cast<int>(buttonState::INACTIVE);

    std::function<void()> m_callback;
};
