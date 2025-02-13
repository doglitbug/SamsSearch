#pragma once

#include "LoaderParams.h"
#include "Vector2D.h"
#include "Managers/AssetManager.h"

class UIObject {
public:
    UIObject()= default;
    ~UIObject() = default;

    virtual void load(const LoaderParams &pParams);
    virtual void draw();
    virtual void update(float deltaTime){};
    virtual void clean(){};

    Vector2D getPosition() const { return m_ScreenPosition; }

    void setPosition(const float x, const float y){
        m_ScreenPosition.setX(x);
        m_ScreenPosition.setY(y);
    };

protected:
    Vector2D m_ScreenPosition;
    std::string m_textureID;
    int m_width = 0;
    int m_height = 0;
};