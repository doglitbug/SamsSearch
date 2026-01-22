#pragma once

#include "UIObject.h"

/// @brief Create an integer label
class LabelInteger : public UIObject {
public:
    LabelInteger() = default;
    ~LabelInteger() = default;

    void update(float deltaTime) override { m_textureID = "int_" + std::to_string(m_link()); };
    void setLink(const std::function<int()>& link) { m_link = link; }

private:
    std::function<int()> m_link;
};