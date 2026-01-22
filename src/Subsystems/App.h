#pragma once

#include <SDL3/SDL.h>

#include "Settings.h"
#include "../States/StateMachine.h"

#define SHOW_HITBOX false

class App
{
public:
    App();
    ~App();

    void render() const;
    void update(float deltaTime) const;
    void handleEvents();
    bool running() const { return m_bRunning; }
    void quit() { m_bRunning = false; }

    Settings* getSettings() { return &m_Settings; }
    Assets* getAssets() const { return m_pAssets; }

    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    StateMachine* getStateMachine() const { return m_pStateMachine; }

    /**
     * @brief Get the size of the screen in pixels, either windowed or full screen
     * @param width
     * @param height
     */
    void getWindowSize(int* width, int* height) const { SDL_GetCurrentRenderOutputSize(m_pRenderer, width, height); }

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    Settings m_Settings;
    Assets* m_pAssets;
    //Engine* m_pEngine; ??
    //Input* m_pInput;
    StateMachine* m_pStateMachine;

    bool m_bRunning;
};

