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
    void parseObjectLayer(XMLElement *pObjectElement, std::vector<GameObjectLayer *> *pLayers) const;

    int m_tileSize;
    int m_width;
    int m_height;
};