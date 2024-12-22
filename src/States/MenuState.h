#pragma once

#include "BaseState.h"
#include "../Managers/EngineStateManager.h"
#include "../Objects/Menus/Title.h"
#include "../Objects/Menus/Button.h"
#include "../Objects/Menus/Label.h"
#include "../Objects/Menus/LabelBoolean.h"
#include "../Objects/Menus/LabelInteger.h"

/// @brief Base state for all menu states
class MenuState : public BaseState
{
public:
    /// @brief Generate Title
    /// @return 
    static UIObject *generateTitle();

    /// @brief Generate page header
    /// @param text for the header
    /// @return
    static UIObject *generateHeader(const std::string &text);

    /// @brief Generate a static label
    /// @param text for the label
    /// @param width of label, default of 200
    /// @return
    static UIObject *generateLabel(const std::string &text, int width = 200);

    /// @brief Generate a On/Off label
    /// @param link boolean function
    /// @param width of label, default of 200
    /// @return
    static UIObject *generateLabel(bool (*link)(), int width = 200);

    /// @brief Generate an integer label
    /// @param link integer function
    /// @param width of label, default of 200
    /// @return
    static UIObject *generateLabel(int (*link)(), int width = 200);

    /// @brief Generate a clickable button
    /// @param text for the button
    /// @param callback function to run when clicked
    /// @param width width of button, default of 200
    /// @return
    static UIObject *generateButton(const std::string &text, void (*callback)(), int width = 200);

protected:
    /// @brief Do nothing, this is only to be used during development as a stub
    static void s_menuToNothing();

    /// @brief Go to previous state by popping state off the stack
    static void s_previousState();
};