#include "InputManager.h"

void InputManager::initializeJoysticks() {
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK)) {
        int i, num_joysticks;
        SDL_JoystickID *joysticks = SDL_GetJoysticks(&num_joysticks);
        if (joysticks) {
            for (i = 0; i < num_joysticks; ++i) {
                SDL_JoystickID instance_id = joysticks[i];
                const char *name = SDL_GetJoystickNameForID(instance_id);
                const char *path = SDL_GetJoystickPathForID(instance_id);

                SDL_Log("Joystick %" SDL_PRIu32 ": %s%s%s VID 0x%.4x, PID 0x%.4x\n",
                        instance_id, name ? name : "Unknown", path ? ", " : "", path ? path : "", SDL_GetJoystickVendorForID(instance_id), SDL_GetJoystickProductForID(instance_id));
            }
            SDL_free(joysticks);
        }
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    }

    //TODO Actually init joysticks, code removed during SDL3 migration!!

    SDL_SetJoystickEventsEnabled(false);
    m_bJoysticksInitialised = false;
}

void InputManager::update() {
    SDL_Event event;
    int whichOne;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                EngineStateManager::get()->quit();
                return;

            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                onJoystickAxisMove(event);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                onJoystickButtonChange(event, true);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
                onJoystickButtonChange(event, false);
                break;

            case SDL_EVENT_MOUSE_MOTION:
                onMouseMove(event);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onMouseButtonChange(event, true);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonChange(event, false);
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                onKeyChange();
                break;
            default:
                break;
        }
    }
}

void InputManager::clean() {
    if (m_bJoysticksInitialised) {
       //TODO Actual code, as this was removed during SDL3 migration
    }
}

// TODO Turn this into a 2d array so we can subscript [joy][stick]->getX()?
// See https://wiki.libsdl.org/SDL2/SDL_JoystickNumAxes and https://wiki.libsdl.org/SDL2/SDL_JoystickGetAxis
int InputManager::xValue(int joy, int stick) {
    if (!m_bJoysticksInitialised)
        return 0;
    switch (stick) {
        case 1:
            return m_joystickValues[joy].first->getX();
        case 2:
            return m_joystickValues[joy].second->getX();
        default:
            return 0;
    }
}

int InputManager::yValue(int joy, int stick) {
    if (!m_bJoysticksInitialised)
        return 0;
    switch (stick) {
        case 1:
            return m_joystickValues[joy].first->getY();
        case 2:
            return m_joystickValues[joy].second->getY();
        default:
            return 0;
    }
}

bool InputManager::getButtonState(int joy, int buttonNumber) {
    return m_buttonStates[joy][buttonNumber];
}

void InputManager::initializeMouse() {
    for (int i = 0; i < 3; i++) {
        m_mouseButtonStates.push_back(false);
    }
    m_mousePosition = Vector2D(0, 0);
}

bool InputManager::getMouseButtonState(int buttonNumber) {
    return m_mouseButtonStates[buttonNumber];
}

Vector2D *InputManager::getMousePosition() {
    return &m_mousePosition;
}

bool InputManager::isKeyDown(SDL_Scancode key) {
    if (!m_keyStates)
        return false;
    return m_keyStates[key] == 1;
}

/**
 * Left and right movement on stick one is axis 0
 * Up and down movement on stick one is axis 1
 * Left and right movement on stick two is axis 3
 * Up and down movement on stick two is axis 4
 * The Xbox 360 controller uses axes 2 and 5 for the analog triggers.
 */
void InputManager::onJoystickAxisMove(SDL_Event &event) {
    int whichOne = event.jaxis.which;
    // left stick move left or right
    if (event.jaxis.axis == 0) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(-1);
        } else {
            m_joystickValues[whichOne].first->setX(0);
        }
    }

    //  left stick up or down
    if (event.jaxis.axis == 1) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setY(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setY(-1);
        } else {
            m_joystickValues[whichOne].first->setY(0);
        }
    }

    // right stick move left or right
    if (event.jaxis.axis == 3) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setX(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setX(-1);
        } else {
            m_joystickValues[whichOne].second->setX(0);
        }
    }

    //  right stick up or down
    if (event.jaxis.axis == 4) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setY(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setY(-1);
        } else {
            m_joystickValues[whichOne].second->setY(0);
        }
    }
}

void InputManager::onJoystickButtonChange(SDL_Event &event, bool state) {
    m_buttonStates[event.jaxis.which][event.jbutton.button] = state;
}

void InputManager::onKeyChange() {
    m_keyStates = SDL_GetKeyboardState(0);
}

void InputManager::onMouseMove(SDL_Event &event) {
    float scale = EngineStateManager::get()->getScale();
    m_mousePosition.setX(event.motion.x / scale);
    m_mousePosition.setY(event.motion.y / scale);
}

void InputManager::onMouseButtonChange(SDL_Event &event, bool state) {
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            m_mouseButtonStates[LEFT] = state;
            break;
        case SDL_BUTTON_MIDDLE:
            m_mouseButtonStates[MIDDLE] = state;
            break;
        case SDL_BUTTON_RIGHT:
            m_mouseButtonStates[RIGHT] = state;
            break;
        default:
            break;
    }
}
