#pragma once

#include "BaseLayer.h"
#include <vector>
#include <cmath>
#include <iostream>

class CollisionLayer: public BaseLayer {
public:
    CollisionLayer() = default;
    ~CollisionLayer() override = default;

    void update(float deltaTime) override {};
    //TODO Display if debug?
    void render(SDL_Rect *pViewport) override {};

    /// @brief Determine if this location is walkable
    /// @param x world location
    /// @param y world location
    /// @return walkable or not
    /// @todo Move to Map?
    bool isWalkable(float x, float y);

private:
    friend class MapParser;
    void setCollisionData(const std::vector<std::vector<int>> &data);

    std::vector<std::vector<int>> m_tileData;
};