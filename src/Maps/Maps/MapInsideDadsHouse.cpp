#include "MapInsideDadsHouse.h"

MapInsideDadsHouse::MapInsideDadsHouse() {
    filename = "assets/maps/InsideDadsHouse.tmx";
}

void MapInsideDadsHouse::load() {
    //TODO Place this into base class as all map will require it!
    MapParser levelParser{};
    levelParser.parseMap(this);

    //Add GOC/GOI that cant be placed into Tiled map, eg because of quests
}