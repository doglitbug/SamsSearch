#include "Teleport.h"

void Teleport::load(int x, int y, int width, int height, const std::map<std::string, std::string> &pCustomProperties) {

    GameObjectItem::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{0, 0, (float) width, (float) height};

    auto cp = CPO(pCustomProperties);
    this->destMap = cp.getString("destMap", "Error");
    this->destX = destX;
    this->destY = destY;
    this->destDirection = destDirection;
}
