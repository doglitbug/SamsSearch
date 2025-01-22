#include "Map.h"
#include "../TinyXML/tinyxml2.h"

using namespace tinyxml2;

class MapParser {
public:
    Map *parseLevel(const char *levelFile);

private:
    static void parseTilesets(XMLElement *pTilesetRoot, std::vector<TileSet> *pTilesets);
    static void parseAdditionalMapProperties(XMLElement *pPropertiesRoot, Map *pLevel);

    void parseTileLayer(XMLElement *pTileElement, std::vector<BaseLayer*> *pLayers, const std::vector<TileSet>* pTilesets) const;
    void parseCollisionLayer(XMLElement *pTileElement, CollisionLayer *pCollisionLayer) const;
    void parseObjectLayer(XMLElement *pObjectElement, std::vector<ObjectLayer *> *pLayers, CollisionLayer *pCollisionLayer) const;

    int m_tileSize;
    int m_width;
    int m_height;
};