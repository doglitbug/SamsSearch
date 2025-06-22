#include "Sign.h"

void Sign::load(const int x, const int y, const int width, const int height, CPO &pCustomProperties) {
    GameObjectItem::load(x, y, width, height, pCustomProperties);
    m_hitBox = new SDL_FRect{0, 0, static_cast<float>(width), static_cast<float>(height)};

    text = pCustomProperties.getStrings("text");
}
