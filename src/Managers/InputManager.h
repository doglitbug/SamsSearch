#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "../Vector2D.h"
#include "EngineStateManager.h"

class InputManager {
public:
    static InputManager *get() {
        static InputManager me;
        return &me;
    };

    InputManager(InputManager &other) = delete;
    void operator=(const InputManager &) = delete;

    void update();
    void clean() const;

    ///
    /// @return Normalized movement vector based on user input
    Vector2D getMovement() const;

    // Joystick Handling
    void initializeGamepads();
    bool getButtonDown(SDL_GamepadButton button) const;
    bool gamepadInUse() const { return m_bGamepad; }

    /// #
    /// @param button
    /// @return
    std::string getButtonLabel(SDL_GamepadButton button) const;

    // Mouse handling
    enum mouse_buttons {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2
    };

    void initializeMouse();
    bool getMouseButtonState(int buttonNumber);
    Vector2D* getMousePosition();

    // Keyboard handling
    bool getKeyDown(SDL_Scancode key) const;

private:
    InputManager() {};
    ~InputManager() {};

    // Mouse
    Vector2D m_mousePosition;
    std::vector<bool> m_mouseButtonStates;
    void onMouseMove(const SDL_Event &event);
    void onMouseButtonChange(const SDL_Event &event);

    // Keyboard
    const bool *m_keyStates;
    void onKeyChange();

    // Joysticks
    /// @brief are we using a GamePad?
    bool m_bGamepad;
    SDL_Gamepad *m_gamepad;
    std::vector<bool> m_buttonStates;
    void onButtonChange(const SDL_Event &event);
};