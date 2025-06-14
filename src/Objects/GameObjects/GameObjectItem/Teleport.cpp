#include "Teleport.h"

void Teleport::load(const int x, const int y, const int width, const int height, CPO &pCustomProperties) {

    GameObjectItem::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{0, 0, static_cast<float>(width), static_cast<float>(height)};

    destMap = pCustomProperties.getString("destMap","Missing map name");
    destX = pCustomProperties.getFloat("destX");
    destY = pCustomProperties.getFloat("destY");
    destDirection = static_cast<DIRECTION>(pCustomProperties.getInt("destDirection", DIRECTION::SOUTH));
}
