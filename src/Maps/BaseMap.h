#pragma once

#include <vector>
#include "BaseLayer.h"
#include "GameObjects/GameObject.h"
#include "CollisionLayer.h"

struct TileSet
{
    int firstgid;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int columns;
    std::string name;
};

class BaseMap {
public:
    BaseMap(){};
    ~BaseMap(){
        // Clean up layers here
        for (auto it = m_upperLayers.begin(); it != m_upperLayers.end();) {
                it = m_upperLayers.erase(it);  // Returns iterator to the next element
        }

        //TODO Is the player in here?
        for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();) {
            it = m_gameObjects.erase(it);  // Returns iterator to the next element
        }

        for (auto it = m_lowerLayers.begin(); it != m_lowerLayers.end();) {
            it = m_lowerLayers.erase(it);  // Returns iterator to the next element
        }
    }

    /// @brief Get TileSets for drawing
    /// @return TileSets
    std::vector<TileSet>* getTileSets(){
        return &m_tileSets;
    }

    std::vector<BaseLayer*>* getLowerLayers(){
        return &m_lowerLayers;
    }

    std::vector<GameObject*>* getGameObjects(){
        return &m_gameObjects;
    }

    std::vector<BaseLayer*>* getUpperLayers(){
        return &m_upperLayers;
    }

    /// @brief Get collision layer
    /// @return Returns pointer to collision layer
    CollisionLayer* getCollisionLayer(){
        return &m_collisionLayer;
    }

    /// @brief Map width in tiles
    int getWidth() const { return width; }

    /// @brief Map height in tiles
    int getHeight() const { return height; };

    std::string getName(){ return name;}
    std::string getFileName(){ return filename;}

    /// @brief Called when the player enters the map
    virtual void onEnter(){};

    /// @brief Called when the player leaves the map
    virtual void onExit(){};

private:
    friend class MapParser;

    std::vector<TileSet> m_tileSets;
    std::vector<BaseLayer*>  m_lowerLayers;
    std::vector<BaseLayer*>  m_upperLayers;
    CollisionLayer m_collisionLayer;
    std::vector<GameObject *> m_gameObjects;

    int width;
    int height;
    std::string name;
protected:
    std::string filename;
};