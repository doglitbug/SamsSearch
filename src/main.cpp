#include "Subsystems/App.h"

constexpr int FPS = 60;
constexpr int DELAY_TIME = static_cast<int>(1000.0f / FPS);

int main(int argc, char *argv[]) {
    App app;
    //TODO Parse command line arguments
    //app.parse(argc, argv)

    float deltaTime = 0;

    while (app.running()) {
        const Uint64 frameStart = SDL_GetTicks();

        //Move all this to the EngineStateManager?
        app.handleEvents();
        app.update(deltaTime);
        app.render();

        //Limit FPS so we don't burn out the GPU (kidding...)
        if (const Uint64 frameTime = SDL_GetTicks() - frameStart; frameTime < DELAY_TIME) {
            SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
        }

        deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
    }

    return 0;
}