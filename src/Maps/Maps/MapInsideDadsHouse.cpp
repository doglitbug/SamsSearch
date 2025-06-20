#include "MapInsideDadsHouse.h"
#include "MapParser.h"

MapInsideDadsHouse::MapInsideDadsHouse() {
    filename = "assets/maps/InsideDadsHouse.tmx";
    MapParser levelParser{};
    levelParser.parseMap(this);
}

void MapInsideDadsHouse::onEnter() {
    //Add GOC/GOI that cant be placed into Tiled map, eg because of quests
}