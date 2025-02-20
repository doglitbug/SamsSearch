#include "MapTest.h"

MapTest::MapTest() {
    filename = "assets/maps/Temp.tmx";
}

void MapTest::load() {
    //TODO Place this into base class as all map will require it!
    MapParser levelParser{};
    levelParser.parseMap(this);

    //Add GOC/GOI that cant be placed into Tiled map, eg because of quests
}
