#include "Managers/EngineStateManager.h"

const int FPS = 60;
const int DELAY_TIME = (int) (1000.0f / FPS);

int main(int argc, char *argv[]) {
    Uint64 frameStart, frameTime;
    float deltaTime = 0;

    // TODO Move these parameters into the init method, as they will be loaded from m_settings and main.cpp doesn't need to know about them
    // TODO Which screen to launch on for those with multi monitor set ups
    if (!EngineStateManager::get()->init("Sam's Search", 100, 100, 1366, 768, false)) {
        std::cout << "Error starting EngineStateManager" << std::endl;
        return -1;
    }

    while (EngineStateManager::get()->running()) {
        frameStart = SDL_GetTicks();

        //Move all this to the EngineStateManager?
        EngineStateManager::get()->handleEvents();
        EngineStateManager::get()->update(deltaTime);
        EngineStateManager::get()->render();

        //Limit FPS so we don't burn out the GPU (kidding...)
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME) {
            SDL_Delay((int) (DELAY_TIME - frameTime));
        }

        deltaTime = (SDL_GetTicks() - frameStart) / 100.0f;
    }
    EngineStateManager::get()->clean();
    return 0;
}