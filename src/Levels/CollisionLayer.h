#pragma once

#include "Layer.h"
#include <vector>
#include <cmath>
#include <iostream>

class CollisionLayer: public Layer {
public:
    CollisionLayer() = default;
    ~CollisionLayer() override = default;

    void update(float deltaTime) override {};
    void render(SDL_Rect *pViewport) override {};
    void setTileData(const std::vector<std::vector<int>> &data);

    /// @brief Determine if this location is walkable
    /// @param x world location
    /// @param y world location
    /// @return walkable or not123
    bool isWalkable(float x, float y);

private:
    std::vector<std::vector<int>> m_tileData;
};