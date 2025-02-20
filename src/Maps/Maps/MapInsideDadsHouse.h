#pragma once

#include "BaseMap.h"
#include "MapParser.h"

class MapInsideDadsHouse : public BaseMap {
public:
    MapInsideDadsHouse();
    void load() override;
};
