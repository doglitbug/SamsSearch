#pragma once

#include <SDL3/SDL_rect.h>

class Layer {
public:
    virtual void render(SDL_Rect *pViewport) = 0;
    virtual void update(float deltaTime) = 0;

protected:
    virtual ~Layer() = default;
};
