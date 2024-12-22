#include "Level.h"
#include "../TinyXML/tinyxml2.h"

using namespace tinyxml2;

class LevelParser {
public:
    Level *parseLevel(const char *levelFile);

private:
    static void parseTilesets(XMLElement *pTilesetRoot, std::vector<TileSet> *pTilesets);
    static void parseAdditionalMapProperties(XMLElement *pPropertiesRoot, Level *pLevel);

    void parseTileLayer(XMLElement *pTileElement, std::vector<Layer*> *pLayers, const std::vector<TileSet>* pTilesets) const;
    void parseCollisionLayer(XMLElement *pTileElement, CollisionLayer *pCollisionLayer) const;
    static void parseObjectLayer(XMLElement *pObjectElement, std::vector<Layer *> *pLayers, CollisionLayer *pCollisionLayer);

    int m_tileSize;
    int m_width;
    int m_height;
};