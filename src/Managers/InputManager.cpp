#include "InputManager.h"

void InputManager::initializeJoysticks() {
    // TODO Check if we were unable to init subsystem and return?
    // TODO Enable using other joysticks?, currently assume to be using XBox controller
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() == 0) {
        m_bJoysticksInitialised = false;
        return;
    }
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        SDL_Joystick *joy = SDL_JoystickOpen(i);
        if (joy) {
            m_joysticks.push_back(joy);
            m_joystickValues.push_back(std::make_pair(new Vector2D(), new Vector2D()));

            std::vector<bool> tempButtons;
            for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
                tempButtons.push_back(false);
            }
            m_buttonStates.push_back(tempButtons);

        } else {
            std::cout << SDL_GetError();
        }
    }

    SDL_JoystickEventState(SDL_ENABLE);
    m_bJoysticksInitialised = true;
}

void InputManager::update() {
    SDL_Event event;
    int whichOne;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                EngineStateManager::get()->quit();
                return;

            case SDL_JOYAXISMOTION:
                onJoystickAxisMove(event);
                break;
            case SDL_JOYBUTTONDOWN:
                onJoystickButtonChange(event, true);
                break;
            case SDL_JOYBUTTONUP:
                onJoystickButtonChange(event, false);
                break;

            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonChange(event, true);
                break;
            case SDL_MOUSEBUTTONUP:
                onMouseButtonChange(event, false);
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                onKeyChange();
                break;
            default:
                break;
        }
    }
}

void InputManager::clean() {
    // TODO What if number of joysticks changes during play, ie a player plugs one in or trips and removes one?
    if (m_bJoysticksInitialised) {
        for (int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_JoystickClose(m_joysticks[i]);
        }
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
    if (!m_keystates)
        return false;
    return m_keystates[key] == 1;
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
    m_keystates = SDL_GetKeyboardState(0);
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
