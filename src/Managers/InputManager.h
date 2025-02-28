#pragma once

#include <iostream>
#include <vector>

#include <SDL3/SDL.h>

#include "EngineStateManager.h"
#include "../Vector2D.h"


class InputManager {
public:
    static InputManager *get() {
        static InputManager me;
        return &me;
    };

    InputManager(InputManager &other) = delete;

    void operator=(const InputManager &) = delete;

    void update();

    void clean();

    // Joystick Handling
    void initializeJoysticks();

    bool joysticksInitialised() { return m_bJoysticksInitialised; }

    int xValue(int joy, int stick);

    int yValue(int joy, int stick);

    bool getButtonState(int joy, int buttonNumber);

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


    bool isKeyDown(SDL_Scancode key);

private:
    InputManager() {};

    ~InputManager() {};

    // Joysticks
    std::vector<SDL_Joystick *> m_joysticks;
    bool m_bJoysticksInitialised;
    std::vector<std::pair<Vector2D *, Vector2D *>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    const int m_joystickDeadZone = 10000; // ToDo Place in m_settings/options?

    // Mouse
    std::vector<bool> m_mouseButtonStates;

    // ToDo Make this a pointer when inputManager is no longer a singleton?
    Vector2D m_mousePosition;

    // Keyboard
    const bool *m_keyStates;

    void onKeyChange();

    void onJoystickAxisMove(SDL_Event &event);

    void onJoystickButtonChange(SDL_Event &event, bool state);

    void onMouseMove(SDL_Event &event);

    void onMouseButtonChange(SDL_Event &event, bool state);
};