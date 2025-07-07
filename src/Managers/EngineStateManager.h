#pragma once

#include <SDL3/SDL.h>

#include "../States/StateMachine.h"

/// @brief Do we want to show object hit-boxes on screen?
#define SHOW_HITBOX false

class EngineStateManager {
public:
    static EngineStateManager *get() {
        static EngineStateManager me;
        return &me;
    };

    EngineStateManager(EngineStateManager &other) = delete;

    void operator=(const EngineStateManager &) = delete;

    bool init(const char *title, int width, int height, bool fullscreen);

    void render() const;

    void update(float deltaTime) const;

    static void handleEvents();

    bool running() const { return m_bRunning; }

    void quit() { m_bRunning = false; }

    [[nodiscard]] SDL_Renderer *getRenderer() const { return m_pRenderer; }

    StateMachine *getStateMachine() { return m_pGameStateMachine; }

    [[nodiscard]] float getScale() const { return m_scale; }
    
    /**
     * @brief Get the size of the screen in pixels, either windowed or full screen
     * @param width
     * @param height
     * @todo Account for SDL_Scale factor if using?
     */
    void getWindowSize(int *width, int *height) const { SDL_GetCurrentRenderOutputSize(m_pRenderer, width, height); }

    static void clean() ;

private:
    EngineStateManager() {}

    ~EngineStateManager() {}

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    /// @brief Internal scaling factor used to account for large screen sizes
    float m_scale;

    bool m_bRunning;
    StateMachine *m_pGameStateMachine;
};