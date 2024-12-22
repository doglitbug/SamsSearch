#include "CollisionLayer.h"
#include <cmath>

void CollisionLayer::setTileIDs(const std::vector<std::vector<int>> &data) {
    m_walkable = data;
}

bool CollisionLayer::isWalkable(float x, float y)
{
    //TODO No magic numbers, this is tile width!
    int cx = std::floor(x / 32.0);
    int cy = std::floor(y / 32.0);
    if (cx < 0 || cx >= m_walkable[0].size() || cy < 0 || cy >= m_walkable.size())
    {
        return false;
    }
    return m_walkable[cy][cx] == 0;
}