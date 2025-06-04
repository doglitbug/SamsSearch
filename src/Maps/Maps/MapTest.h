#pragma once

#include "BaseMap.h"
#include "MapParser.h"

class MapTest : public BaseMap {
public:
    MapTest();
    void onEnter() override;
};
