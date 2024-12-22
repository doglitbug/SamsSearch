#pragma once

#include <string>
#include <map>
#include "Objects/GameObjects/GameObject.h"

class BaseCreator {
public:
    virtual GameObject *createGameObject() = 0;
    virtual ~BaseCreator() = default;
};

class GameObjectFactory {
public:
    static GameObjectFactory *get() {
        static GameObjectFactory me;
        return &me;
    };

    //Remove copy constructor
    GameObjectFactory(GameObjectFactory const &) = delete;

    //Remove load operator
    void operator=(GameObjectFactory const &) = delete;

    bool registerType(const std::string& ID, BaseCreator *pCreator) {
        std::map<std::string, BaseCreator *>::iterator it = m_creators.find(ID);
        //If already registered, do nothing
        if (it != m_creators.end()) {
            delete pCreator;
            return false;
        }

        m_creators[ID] = pCreator;
        return true;
    }

    GameObject *create(const std::string &ID) {
        std::map<std::string, BaseCreator *>::iterator it = m_creators.find(ID);
        if (it == m_creators.end()) {
            std::cout << "Could not find type: " << ID << std::endl;
            return nullptr;
        }

        BaseCreator *pCreator = (*it).second;
        return pCreator->createGameObject();
    }

private:
    GameObjectFactory() = default;
    ~GameObjectFactory() = default;

    std::map<std::string, BaseCreator *> m_creators;
};