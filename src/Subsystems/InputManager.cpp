#include "InputManager.h"

void InputManager::initializeGamepads() {
    if (!SDL_HasGamepad()) {
        SDL_Log("No Gamepads connected");
        m_bGamepad = false;
        return;
    }

    int count;
    auto joystickIDs = SDL_GetGamepads(&count);
    if (!joystickIDs) {
        SDL_Log("Unable to get joystick IDs");
        m_bGamepad = false;
        return;
    }

    m_gamepad = SDL_OpenGamepad(joystickIDs[0]);
    SDL_Log("%s connected", SDL_GetGamepadName(m_gamepad));
    SDL_RumbleGamepad(m_gamepad, 0xffff, 0xffff, 500);

    SDL_free(joystickIDs);

    //TODO Deal with unplugging and plugging in during game, may need to move some of this code to a separate function
    //TODO Allow user to select which Gamepad to use in settings?

    //Set the size of button Array!
    m_buttonStates.resize(SDL_GAMEPAD_BUTTON_COUNT, false);

    //It looks like we are all good
    m_bGamepad = true;
}

InputManager::InputManager(App* pSDLApplication)
{
    m_pApplication = pSDLApplication;
}

void InputManager::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                m_pApplication->quit();
                return;

            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                onButtonChange(event);
                break;

            case SDL_EVENT_MOUSE_MOTION:
                onMouseMove(event);
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonChange(event);
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

void InputManager::clean() const {
    if (m_bGamepad) {
        SDL_CloseGamepad(m_gamepad);
    }
}

Vector2D InputManager::getMovement() const {
    Vector2D newVelocity = {0, 0};

    //TODO Make these changeable in settings and or move to WASD!
    if (getKeyDown(SDL_SCANCODE_RIGHT) || getButtonDown(SDL_GAMEPAD_BUTTON_DPAD_RIGHT)) {
        newVelocity.setX(1);
    } else if (getKeyDown(SDL_SCANCODE_LEFT) || getButtonDown(SDL_GAMEPAD_BUTTON_DPAD_LEFT)) {
        newVelocity.setX(-1);
    }

    if (getKeyDown(SDL_SCANCODE_DOWN) || getButtonDown(SDL_GAMEPAD_BUTTON_DPAD_DOWN)) {
        newVelocity.setY(1);
    } else if (getKeyDown(SDL_SCANCODE_UP) || getButtonDown(SDL_GAMEPAD_BUTTON_DPAD_UP)) {
        newVelocity.setY(-1);
    }

    // Pythagoras thou art a heartless bitch
    newVelocity.normalize();

    return newVelocity;
}

bool InputManager::getButtonDown(const SDL_GamepadButton button) const {
    //Allow us to check if a button is pressed without first checking if there is an active gamepad
    if (!m_bGamepad) return false;

    return m_buttonStates[button];
}

std::string InputManager::getButtonLabel(const SDL_GamepadButton button) const {
    if (!m_bGamepad) return "";

    switch (SDL_GetGamepadButtonLabel(m_gamepad, button)) {
        case SDL_GAMEPAD_BUTTON_LABEL_A:
            return "A";
        case SDL_GAMEPAD_BUTTON_LABEL_B:
            return "B";
        case SDL_GAMEPAD_BUTTON_LABEL_X:
            return "X";
        case SDL_GAMEPAD_BUTTON_LABEL_Y:
            return "Y";
        case SDL_GAMEPAD_BUTTON_LABEL_CROSS:
            return "X";
        case SDL_GAMEPAD_BUTTON_LABEL_CIRCLE:
            return "O";
        case SDL_GAMEPAD_BUTTON_LABEL_SQUARE:
            return "Square";
        case SDL_GAMEPAD_BUTTON_LABEL_TRIANGLE:
            return "Triangle";
        default:
            return "Non face key!";
    }
}

void InputManager::initializeMouse() {
    for (int i = 0; i < 3; i++) {
        m_mouseButtonStates.push_back(false);
    }
    m_mousePosition = Vector2D(0, 0);
}

bool InputManager::getMouseButtonState(const int buttonNumber) {
    return m_mouseButtonStates[buttonNumber];
}

Vector2D *InputManager::getMousePosition() {
    return &m_mousePosition;
}

bool InputManager::getKeyDown(const SDL_Scancode key) const {
    if (!m_keyStates)
        return false;
    return m_keyStates[key] == 1;
}

void InputManager::onButtonChange(const SDL_Event &event) {
    SDL_Log("Pressed %s", getButtonLabel(static_cast<SDL_GamepadButton>(event.gbutton.button))
            .c_str());
    m_buttonStates[event.gbutton.button] = event.gbutton.down;
}

void InputManager::onKeyChange() {
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void InputManager::onMouseMove(const SDL_Event &event) {
    const float scale = 1.0f;
    //TODO Make this a setting?
    m_mousePosition.setX(event.motion.x / scale);
    m_mousePosition.setY(event.motion.y / scale);
}

void InputManager::onMouseButtonChange(const SDL_Event &event) {
    const bool state = event.button.down;
    //TODO Refactor this like onButtonChange
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
