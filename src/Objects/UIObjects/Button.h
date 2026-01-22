#pragma once

#include <functional>

#include "UIObject.h"

/// @brief Create a clickable button
class Button : public UIObject {
public:
    Button() {};
    ~Button() {};

    void load(const LoaderParams &pParams) override;
    void update(float deltaTime) override;

    void setCallback(const std::function<void()>& callback) { m_callback = callback; }

private:
    enum buttonState {
        INACTIVE = 0,
        ACTIVE = 1,
        SELECTED = 2,
    };
    bool m_bReleased;
    int m_currentFrame;

    std::function<void()> m_callback;
};