#pragma once

#include <vector>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../Objects/BaseObject.h"
#include "../States/StateMachine.h"
#include "../Vector2D.h"

class EngineStateManager {
public:
    static EngineStateManager *get() {
        static EngineStateManager me;
        return &me;
    };

    EngineStateManager(EngineStateManager &other) = delete;

    void operator=(const EngineStateManager &) = delete;

    bool init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void render();

    void update(float deltaTime);

    static void handleEvents();

    bool running() const { return m_bRunning; }

    void quit() { m_bRunning = false; }

    [[nodiscard]] SDL_Renderer *getRenderer() const { return m_pRenderer; }

    StateMachine *getStateMachine() { return m_pGameStateMachine; }

    [[nodiscard]] float getScale() const { return m_scale; }
    
    /**
     * @brief Get size of the screen in pixels, either windowed or full screen
     * @param width
     * @param height
     * @todo Account for SDL_Scale factor if using?
     */
    void getWindowSize(int *width, int *height) { SDL_GetRendererOutputSize(m_pRenderer, width, height); }

    void clean();

private:
    EngineStateManager() {}

    ~EngineStateManager() {}

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    /// @brief Internal scaling factor used to account for large screen sizes
    float m_scale;

    bool m_bRunning;
    StateMachine *m_pGameStateMachine;

    /// @brief Used to calculate camera position later on
    Vector2D *m_playerLocation;
};