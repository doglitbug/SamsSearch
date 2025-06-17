#pragma once
#include "BaseMap.h"
#include "../TinyXML/tinyxml2.h"

using namespace tinyxml2;

class MapParser {
public:
    void parseMap(BaseMap * pMap);

private:
    static void parseTilesets(XMLElement *pTilesetRoot, std::vector<TileSet> *pTilesets);
    static void parseAdditionalMapProperties(XMLElement *pPropertiesRoot, BaseMap *pLevel);

    void parseTileLayer(XMLElement *pTileElement, std::vector<BaseLayer*> *pLayers, const std::vector<TileSet>* pTilesets) const;
    void parseCollisionLayer(XMLElement *pCollisionElement, CollisionLayer *pCollisionLayer) const;
    static void parseObjectLayer(XMLElement *pObjectElement, std::vector<GameObjectLayer *> *pLayers);

    int m_tileSize = 0;
    int m_width = 0;
    int m_height = 0;
};