#include "Dog.h"

Dog::Dog() {}

void Dog::load(const LoaderParams *pParams) {
    NPC::load(pParams);
    //TODO multiple by scale!
    m_hitBox = new SDL_Rect{6, 22, 14, 14};
}
