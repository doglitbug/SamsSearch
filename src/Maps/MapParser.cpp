#include <regex>
#include "MapParser.h"
#include "TileLayer.h"
#include "zlib.h"
#include "base64.h"
#include "GameObjectLayer.h"
#include "Objects/GameObjects/GameObjectFactory.h"

void MapParser::parseMap(BaseMap *pMap)
{
    auto mapFile = pMap->filename;

    // Create an XML document and load the map XML
    XMLDocument levelDocument = XMLDocument(false, COLLAPSE_WHITESPACE);
    levelDocument.LoadFile(mapFile.c_str());

    // Get the root node
    XMLElement *pRoot = levelDocument.RootElement();

    m_tileSize = pRoot->IntAttribute("tilewidth");
    m_width = pRoot->IntAttribute("width");
    m_height = pRoot->IntAttribute("height");

    for (XMLElement *e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("properties"))
        {
            parseAdditionalMapProperties(e, pMap);
        }
        else if (e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pMap->getTileSets());
        }
        else if (e->Value() == std::string("layer"))
        {
            std::string layerClass = e->Attribute("class");

            if (layerClass == "Lower") {
                parseTileLayer(e, pMap->getLowerLayers(), pMap->getTileSets());
            } else if (layerClass == "Upper") {
                parseTileLayer(e, pMap->getUpperLayers(), pMap->getTileSets());
            } else if (layerClass == "Collision") {
                parseCollisionLayer(e, pMap->getCollisionLayer());
            } else {
                std::cout << "Unknown layer class: " << layerClass << std::endl;
            }
        }
        else if (e->Value() == std::string("objectgroup"))
        {
            parseObjectLayer(e, pMap->getObjectLayers());
        }
        else
        {
            std::cout << "Unknown value: " << e->Value() << std::endl;
        }
    }
}

void MapParser::parseTilesets(XMLElement *pTilesetRoot, std::vector<TileSet> *pTilesets)
{
    // First add the tileset to the texture manager (from image element)
    // Adjust source to point to correct location (swap '..' for 'assets'
    std::string sourceLocation = pTilesetRoot->FirstChildElement()->Attribute("source");
    sourceLocation = "assets" + sourceLocation.substr(2);

    AssetManager::get()->loadTexture(sourceLocation,
                                     pTilesetRoot->Attribute("name"));
    TileSet tileset;
    tileset.width = pTilesetRoot->FirstChildElement()->IntAttribute("width");
    tileset.height = pTilesetRoot->FirstChildElement()->IntAttribute("height");
    tileset.firstgid = pTilesetRoot->IntAttribute("firstgid");
    tileset.tileWidth = pTilesetRoot->IntAttribute("tilewidth");
    tileset.tileHeight = pTilesetRoot->IntAttribute("tileheight");
    tileset.spacing = pTilesetRoot->IntAttribute("spacing", 0);
    tileset.margin = pTilesetRoot->IntAttribute("margin", 0);
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.columns = pTilesetRoot->IntAttribute("columns");

    pTilesets->push_back(tileset);
}

void MapParser::parseAdditionalMapProperties(XMLElement *pPropertiesRoot, BaseMap *pLevel)
{
    for (XMLElement *e = pPropertiesRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("property"))
        {
            std::string attributeName = e->Attribute("name");

            if(attributeName == "name") {
                pLevel->name = e->Attribute("value");
            } else {
                std::cout << "Unknown attribute name: " << attributeName <<std::endl;
            }
        }
        else
        {
            std::cout << "Unknown property value: " << e->Value() << std::endl;
        }
    }
}

void MapParser::parseTileLayer(XMLElement *pTileElement, std::vector<BaseLayer *> *pLayers,
                               const std::vector<TileSet> *pTilesets) const
{
    auto *pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    // Tile Data
    std::vector<std::vector<int>> data;
    std::string decodedIDs;
    XMLElement *pDataNode;

    for (XMLElement *e = pTileElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
        else
        {
            std::cout << "Unknown TileLayer value: " << e->Value() << std::endl;
        }
    }

    for (XMLNode *e = pDataNode->FirstChild(); e != nullptr; e = e->NextSibling())
    {
        XMLText *text = e->ToText();
        // RegEx used because COLLAPSE_WHITESPACE Seems to not get set properly and the newlines output to the XMl from Tiled, crash base64 :-(
        const std::string t = std::regex_replace(text->Value(), std::regex("\\s+"), "");
        decodedIDs = base64_decode(t, true);
    }

    // uncompress zlib contents
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef *)&gids[0], &numGids, (const Bytef *)decodedIDs.c_str(), decodedIDs.size());
    std::vector<int> layerRow(m_width);
    for (int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++)
    {
        for (int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = (int)gids[rows * m_width + cols];
        }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}

void MapParser::parseCollisionLayer(XMLElement *pCollisionElement, CollisionLayer *pCollisionLayer) const
{
    // Tile Data
    std::vector<std::vector<int>> data;
    std::string decodedIDs;
    XMLElement *pDataNode;

    for (XMLElement *e = pCollisionElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
        else
        {
            std::cout << "Unknown TileLayer value: " << e->Value() << std::endl;
        }
    }

    for (XMLNode *e = pDataNode->FirstChild(); e != nullptr; e = e->NextSibling())
    {
        XMLText *text = e->ToText();
        // RegEx used because COLLAPSE_WHITESPACE Seems to not get set properly and the newlines output to the XMl from Tiled, crash base64 :-(
        const std::string t = std::regex_replace(text->Value(), std::regex("\\s+"), "");
        decodedIDs = base64_decode(t, true);
    }

    // uncompress zlib contents
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef *)&gids[0], &numGids, (const Bytef *)decodedIDs.c_str(), decodedIDs.size());
    std::vector<int> layerRow(m_width);
    for (int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++)
    {
        for (int cols = 0; cols < m_width; cols++)
        {
            // filled gids are not 1, due to ordering of tile sheets, walkable will be 1 or 0 at this stage (not 0.75 for mud etc)
            // TODO Figure how to change collision layer to have one way etc
            // GID 1 = walkable, all else not walkable
            data[rows][cols] = gids[rows * m_width + cols] == 1 ? 0 : 1;
        }
    }

    pCollisionLayer->setCollisionData(data);
}


// ToDo BaseObject layers, do these need to be loaded from a save file for each level?
void MapParser::parseObjectLayer(XMLElement *pObjectElement, std::vector<GameObjectLayer *> *pLayers) const
{
    // Create an object layer
    auto *pObjectLayer = new GameObjectLayer();
    for (XMLElement *e = pObjectElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("object"))
        {
            int x, y, width, height;

            //, startColumn, startRow; std::string textureID;

            // Get values on the object node (this will exist for all Game Objects)
            x = e->IntAttribute("x");
            y = e->IntAttribute("y");
            width = e->IntAttribute("width");
            height = e->IntAttribute("height");

            GameObject *pGameObject = GameObjectFactory::get()->create(e->Attribute("type"));

            //Get additional properties that may be different for different GameObjects and place in a map
            auto customProperties = std::map<std::string, std::string>();

            //TODO Check to see if this object has <properties>
            if (e->FirstChildElement("properties") != nullptr) {
                for (XMLElement *property = e->FirstChildElement()->FirstChildElement();
                     property != nullptr; property = property->NextSiblingElement())
                {
                    auto key = property->Attribute("name");
                    auto value = property->Attribute("value");

                    customProperties[key]=value;
                }
            }

            CPO prop = CPO(customProperties);
            pGameObject->load(x, y, width, height, prop);

            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
        else
        {
            std::cout << "Unknown GameObjectLayer value: " << e->Value() << std::endl;
        }
    }

    pLayers->push_back(pObjectLayer);
}
