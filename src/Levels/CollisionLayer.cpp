#include "CollisionLayer.h"


void CollisionLayer::setCollisionData(const std::vector<std::vector<int>> &data) {
    m_tileData = data;
}

bool CollisionLayer::isWalkable(float x, float y)
{
    //TODO No magic numbers, this is tile width!
    int cx = std::floor(x / 32.0);
    int cy = std::floor(y / 32.0);
    if (cx < 0 || cx >= m_tileData[0].size() || cy < 0 || cy >= m_tileData.size())
    {
        return false;
    }
    return m_tileData[cy][cx] == 0;
}