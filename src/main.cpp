#include "Managers/EngineStateManager.h"

constexpr int FPS = 60;
constexpr int DELAY_TIME = static_cast<int>(1000.0f / FPS);

int main(int argc, char *argv[]) {
    float deltaTime = 0;

    // TODO Move these parameters into the init method, as they will be loaded from m_settings and main.cpp doesn't need to know about them
    // TODO Which screen to launch on for those with multi monitor set ups
    if (!EngineStateManager::get()->init("Sam's Search", 1280, 1024, false)) {
        std::cout << "Error starting EngineStateManager" << std::endl;
        return -1;
    }

    while (EngineStateManager::get()->running()) {
        const Uint64 frameStart = SDL_GetTicks();

        //Move all this to the EngineStateManager?
        EngineStateManager::get()->handleEvents();
        EngineStateManager::get()->update(deltaTime);
        EngineStateManager::get()->render();

        //Limit FPS so we don't burn out the GPU (kidding...)
        if (const Uint64 frameTime = SDL_GetTicks() - frameStart; frameTime < DELAY_TIME) {
            SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
        }

        deltaTime = (SDL_GetTicks() - frameStart) / 100.0f;
    }
    EngineStateManager::get()->clean();
    return 0;
}