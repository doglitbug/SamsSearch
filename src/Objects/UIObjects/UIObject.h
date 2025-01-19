#pragma once

#include "BaseObject.h"
#include "Managers/AssetManager.h"

/// @brief BaseObject for User Interface
class UIObject : public BaseObject {
public:
    UIObject()= default;
    ~UIObject() = default;

    void load(const LoaderParams &pParams) override;
    void draw();
    void update(float deltaTime) override {};
    void clean() override {};

    void setPosition(float x, float y){
        m_position.setX(x);
        m_position.setY(y);
    };
};