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
    ~Level(){};
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