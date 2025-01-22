#pragma once

#include "Map.h"
#include "BaseLayer.h"

class TileLayer : public BaseLayer {
public:
    TileLayer(int tileSize, const std::vector<TileSet> &tileSets);

    void update(float deltaTime) override;

    void render(SDL_Rect *pViewport) override;

    void setTileIDs(const std::vector<std::vector<int>> &data) {
        m_tileIDs = data;
    }

private:
    int m_tileSize;

    TileSet getTileSetByID(int tileID);

    const std::vector<TileSet> &m_tileSets;
    std::vector<std::vector<int>> m_tileIDs;

    /**
     * Get a tile ID
     * @param x
     * @param y
     * @return tile Id at specified location OR 0 if out of bounds
     */
    int getID(int x, int y) {
        if (x < 0 || x >= m_tileIDs[0].size() || y < 0 || y >= m_tileIDs.size()) {
            return 0;
        }
        return m_tileIDs[y][x];
    }
};