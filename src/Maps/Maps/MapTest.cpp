#include "MapTest.h"
#include "MapParser.h"

MapTest::MapTest() {
    filename = "assets/maps/Temp.tmx";
    MapParser levelParser{};
    levelParser.parseMap(this);
}

void MapTest::onEnter() {
    //Add GOC/GOI that cant be placed into Tiled map, eg because of quests
}
