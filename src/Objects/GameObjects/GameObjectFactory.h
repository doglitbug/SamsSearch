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
        auto it = m_creators.find(ID);
        //If already registered, do nothing
        if (it != m_creators.end()) {
            delete pCreator;
            return false;
        }

        m_creators[ID] = pCreator;
        return true;
    }

    GameObject *create(const std::string &ID) {
        const auto it = m_creators.find(ID);
        if (it == m_creators.end()) {
            std::cout << "Could not find map object type: " << ID << std::endl;
            return nullptr;
        }

        BaseCreator *pCreator = (*it).second;
        return pCreator->createGameObject();
    }

private:
    GameObjectFactory() = default;
    ~GameObjectFactory() {
        for (auto it = m_creators.cbegin(); it != m_creators.cend() /* not hoisted */; /* no increment */) {
            delete it->second;
            m_creators.erase(it++);
        }
    };

    std::map<std::string, BaseCreator *> m_creators;
};