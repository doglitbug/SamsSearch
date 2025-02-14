#include "Teleport.h"

void Teleport::load(int x, int y, int width, int height, CPO &pCustomProperties) {

    GameObjectItem::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{0, 0, (float) width, (float) height};

    destMap = pCustomProperties.getString("destMap","Missing mapname");
    destX = pCustomProperties.getFloat("destX");
    destY = pCustomProperties.getFloat("destY");
    //TODO Actually read from map
    destDirection = DIRECTION::SOUTH;
}
