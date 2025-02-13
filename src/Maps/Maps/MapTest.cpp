#include "MapTest.h"

#include "MapParser.h"

MapTest::MapTest() {
    //TODO Place this into base class as all map will require it!
    MapParser levelParser{};
    filename = "assets/maps/Temp.tmx";
    levelParser.parseMap(this);

    //Add GOC/GOI that cant be placed into Tiled map, eg because of quests
}
