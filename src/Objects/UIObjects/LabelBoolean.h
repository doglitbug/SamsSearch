#pragma once

#include "UIObject.h"

/// @brief Create a on/off label
class LabelBoolean : public UIObject {
public:
    LabelBoolean() = default;
    ~LabelBoolean() = default;

    void update(float deltaTime) override { m_textureID = m_link() ? "toggle_On" : "toggle_Off"; };
    void setLink(const std::function<bool()>& link) { m_link = link; }

private:
    std::function<bool()> m_link;
};