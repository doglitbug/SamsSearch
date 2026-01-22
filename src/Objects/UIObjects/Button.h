#pragma once

#include <functional>
#include <utility>
#include "UIObject.h"

/// @brief Create a clickable button
class Button : public UIObject {
public:
    void load(const LoaderParams &pParams) override;
    void update(float deltaTime) override;

    void setCallback(std::function<void()> callback) { m_callback = std::move(callback); }

private:
    enum buttonState {
        INACTIVE = 0,
        ACTIVE = 1,
        SELECTED = 2,
    };
    bool m_bReleased= false;
    int m_currentFrame = INACTIVE;

    std::function<void()> m_callback;
};