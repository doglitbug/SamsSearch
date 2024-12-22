#include "TileLayer.h"
#include "../Managers/EngineStateManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<TileSet> &tileSets) : m_tileSize(tileSize), m_tileSets(tileSets) {

}

void TileLayer::update(float deltaTime) {
    //ToDo Animation here?
}

void TileLayer::render(SDL_Rect *pViewport) {
    int xTile, yTile, xTileOffset, yTileOffset;

    //TODO Move this to Settings, and only recalculate it when screen size/scale changes rather than here?
    int m_numColumns = pViewport->w / m_tileSize;
    int m_numRows = pViewport->h / m_tileSize;

    xTile = pViewport->x / m_tileSize;
    yTile = pViewport->y / m_tileSize;
    xTileOffset = pViewport->x % m_tileSize;
    yTileOffset = pViewport->y % m_tileSize;

    //Add 1 to overdraw and smooth out tiles 'popping in'
    for (int i = 0; i < m_numRows+1; i++) {
        for (int j = 0; j < m_numColumns+1; j++) {
            int id = getID(j + xTile, i + yTile);
            if (id == 0) {
                continue;
            }
            TileSet tileSet = getTileSetByID(id);
            id--;
            AssetManager::get()->drawTile(tileSet.name, tileSet.margin, tileSet.spacing,
                                          (j * m_tileSize) - xTileOffset, (i * m_tileSize) - yTileOffset, m_tileSize,
                                          m_tileSize, (id - (tileSet.firstgid - 1)) /
                                                      tileSet.columns, (id - (tileSet.firstgid - 1)) %
                                                                       tileSet.columns);
        }
    }
}

TileSet TileLayer::getTileSetByID(int tileID) {
    for (int i = 0; i < m_tileSets.size(); i++) {
        if (i + 1 <= m_tileSets.size() - 1) {
            if (tileID >= m_tileSets[i].firstgid && tileID < m_tileSets[i + 1].firstgid) {
                return m_tileSets[i];
            }
        } else {
            return m_tileSets[i];
        }
    }
    std::cout << "did not find tileSet, returning empty tileSet\n";
    TileSet t;
    return t;
}
