#pragma once

#include <SDL3/SDL.h>

#include "Settings.h"
#include "Subsystems/Assets.h"
#include "Subsystems/InputSystem.h"
#include "InputSystem.h"
#include "../States/StateMachine.h"

#define SHOW_HITBOX false

class App
{
public:
    static App* get()
    {
        static App me;
        return &me;
    };

    // Singleton
    App(App& other) = delete;
    void operator=(const App&) = delete;

    void init();
    void render() const;
    void update(float deltaTime) const;
    void handleEvents() const;
    bool running() const { return m_bRunning; }
    void quit() { m_bRunning = false; }

    Settings* getSettings() { return m_pSettings; }
    Assets* getAssets() const { return m_pAssets; }
    InputSystem* getInput() const { return m_pInput; }

    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    StateMachine* getStateMachine() const { return m_pStateMachine; }

    /**
     * @brief Get the size of the screen in pixels, either windowed or full screen
     * @param width
     * @param height
     */
    void getWindowSize(int* width, int* height) const { SDL_GetCurrentRenderOutputSize(m_pRenderer, width, height); }

private:
    App() = default;
    ~App() = default;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    Settings* m_pSettings;
    Assets* m_pAssets;
    //Engine* m_pEngine; ??
    InputSystem* m_pInput;
    StateMachine* m_pStateMachine;

    bool m_bRunning;
};

