#include "InputSystem.h"
#include "App.h"

void InputSystem::initializeGamepads()
{
    if (!SDL_HasGamepad())
    {
        SDL_Log("No Gamepads connected");
        m_bGamepad = false;
        return;
    }

    int count;
    auto joystickIDs = SDL_GetGamepads(&count);
    if (!joystickIDs)
    {
        SDL_Log("Unable to get joystick IDs");
        m_bGamepad = false;
        return;
    }

    m_gamepad = SDL_OpenGamepad(joystickIDs[0]);
    SDL_Log("%s connected", SDL_GetGamepadName(m_gamepad));
    SDL_RumbleGamepad(m_gamepad, 0xffff, 0xffff, 500);

    SDL_free(joystickIDs);

    // TODO Deal with unplugging and plugging in during game, may need to move some of this code to a separate function
    // TODO Allow user to select which Gamepad to use in settings?

    // Set the size of button Array!
    m_buttonStates.resize(SDL_GAMEPAD_BUTTON_COUNT, false);

    // It looks like we are all good
    m_bGamepad = true;
}

void InputSystem::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            App::get()->quit();
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

void InputSystem::clean() const
{
    if (m_bGamepad)
    {
        SDL_CloseGamepad(m_gamepad);
    }
}

Vector2D InputSystem::getMovement() const
{
    Vector2D newVelocity = {0, 0};

    if (getKeyDown(App::get()->getSettings()->m_keyboard.RIGHT) || getButtonDown(App::get()->getSettings()->m_gamepad.RIGHT))
    {
        newVelocity.setX(1);
    }
    else if (getKeyDown(App::get()->getSettings()->m_keyboard.LEFT) || getButtonDown(App::get()->getSettings()->m_gamepad.LEFT))
    {
        newVelocity.setX(-1);
    }

    if (getKeyDown(App::get()->getSettings()->m_keyboard.DOWN) || getButtonDown(App::get()->getSettings()->m_gamepad.DOWN))
    {
        newVelocity.setY(1);
    }
    else if (getKeyDown(App::get()->getSettings()->m_keyboard.UP) || getButtonDown(App::get()->getSettings()->m_gamepad.UP))
    {
        newVelocity.setY(-1);
    }

    // Pythagoras thou art a heartless bitch
    newVelocity.normalize();

    return newVelocity;
}

bool InputSystem::getAction(actions action)
{
    switch (action)
    {
    case actions::MENU:
        return getKeyDown(App::get()->getSettings()->m_keyboard.MENU) || getButtonDown(App::get()->getSettings()->m_gamepad.MENU);
        break;
    case actions::ATTACK:
        return getKeyDown(App::get()->getSettings()->m_keyboard.ATTACK) || getButtonDown(App::get()->getSettings()->m_gamepad.ATTACK);
        break;
    case actions::SECONDARY_ATTACK:
        return getKeyDown(App::get()->getSettings()->m_keyboard.SECONDARY_ATTACK) || getButtonDown(App::get()->getSettings()->m_gamepad.SECONDARY_ATTACK);
        break;
    case actions::CONFIRM:
        return getKeyDown(App::get()->getSettings()->m_keyboard.CONFIRM) || getButtonDown(App::get()->getSettings()->m_gamepad.CONFIRM);
        break;
    case actions::CANCEL:
        return getKeyDown(App::get()->getSettings()->m_keyboard.CANCEL) || getButtonDown(App::get()->getSettings()->m_gamepad.CANCEL);
        break;
    }
    return false;
}

bool InputSystem::getButtonDown(const int button) const
{
    // Allow us to check if a button is pressed without first checking if there is an active gamepad
    if (!m_bGamepad)
        return false;

    return m_buttonStates[button];
}

std::string InputSystem::getButtonLabel(const SDL_GamepadButton button) const
{
    if (!m_bGamepad)
        return "";

    switch (SDL_GetGamepadButtonLabel(m_gamepad, button))
    {
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

void InputSystem::initializeMouse()
{
    for (int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
    m_mousePosition = Vector2D(0, 0);
}

bool InputSystem::getMouseButtonState(const int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}

Vector2D *InputSystem::getMousePosition()
{
    return &m_mousePosition;
}

bool InputSystem::getKeyDown(const int key) const
{
    if (!m_keyStates)
        return false;
    return m_keyStates[key] == 1;
}

void InputSystem::onButtonChange(const SDL_Event &event)
{
    m_buttonStates[event.gbutton.button] = event.gbutton.down;
}

void InputSystem::onKeyChange()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void InputSystem::onMouseMove(const SDL_Event &event)
{
    const float scale = 1.0f;
    // TODO Make this a setting?
    m_mousePosition.setX(event.motion.x / scale);
    m_mousePosition.setY(event.motion.y / scale);
}

void InputSystem::onMouseButtonChange(const SDL_Event &event)
{
    const bool state = event.button.down;
    // TODO Refactor this like onButtonChange
    switch (event.button.button)
    {
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
