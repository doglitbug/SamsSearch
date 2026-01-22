#pragma once

#include <string>
#include <vector>

#include "UIObject.h"

class BaseState {
public:
    virtual ~BaseState() = default;
    //Must be overridden in children
    virtual void onEnter() = 0;

    //May be overridden, but will probably call
    virtual void update(float deltaTime){
        for (UIObject *go: m_gameObjects) {
            go->update(deltaTime);
        }
    };

    //May be overridden, but will probably not be implemented at all
    virtual void render() {
        for (UIObject *go: m_gameObjects) {
            go->draw();
        }
    };

    //May be overridden, but will probably call
    virtual void onExit() {
        for (UIObject *go: m_gameObjects) {
            go->clean();
            delete go;
        }
        m_gameObjects.clear();

        //Clear the texture manager (never used)
        for(const auto & id : m_textureIDList)
        {
            //TODO Assets::get()->deleteTexture(id);
        }
    }

protected:
    std::vector<UIObject *> m_gameObjects;
    std::vector<std::string> m_textureIDList;
};