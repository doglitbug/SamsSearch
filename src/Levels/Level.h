#pragma once

#include <iostream>
#include <vector>
#include "Layer.h"
#include "CollisionLayer.h"
#include "Vector2D.h"
#include "ObjectLayer.h"

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

class Level {
public:
    ~Level(){

        // Clean up layers here

        for (auto it = m_upperLayers.begin(); it != m_upperLayers.end();) {
                it = m_upperLayers.erase(it);  // Returns iterator to the next element
        }

        for (auto it = m_objectLayers.begin(); it != m_objectLayers.end();) {
            it = m_objectLayers.erase(it);  // Returns iterator to the next element
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

    std::vector<Layer*>* getLowerLayers(){
        return &m_lowerLayers;
    }

    std::vector<ObjectLayer*>* getObjectLayers(){
        return &m_objectLayers;
    }

    std::vector<Layer*>* getUpperLayers(){
        return &m_upperLayers;
    }

    /// @brief Get collision layer
    /// @return Returns pointer to collision layer
    CollisionLayer* getCollisionLayer(){
        return &m_collisionLayer;
    }

    /// @brief Map width in tiles
    [[nodiscard]] int getWidth() const { return width; }
    /// @brief Map height in tiles
    [[nodiscard]] int getHeight() const { return height; };

    std::string getName(){ return name;}

private:
    friend class LevelParser;
    Level(){};

    std::vector<TileSet> m_tileSets;
    std::vector<Layer*>  m_lowerLayers;
    std::vector<ObjectLayer*>  m_objectLayers;
    std::vector<Layer*>  m_upperLayers;
    CollisionLayer m_collisionLayer;

    int width;
    int height;
    std::string name;
};