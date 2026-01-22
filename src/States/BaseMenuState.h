#pragma once

#include "BaseState.h"
#include "../Subsystems/App.h"
#include "Objects/UIObjects/Title.h"
#include "Objects/UIObjects/Button.h"
#include "Objects/UIObjects/Label.h"
#include "Objects/UIObjects/LabelBoolean.h"
#include "Objects/UIObjects/LabelInteger.h"

#include <functional>

//Default sizes
#define ROW_HEIGHT 50
#define ROW_GAP 15

#define BUTTON_WIDTH 200
#define LABEL_WIDTH 200

#define HEADER_WIDTH 700
#define HEADER_HEIGHT 150
/// @brief Base state for all menu states
class BaseMenuState : public BaseState
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
    static UIObject *generateLabel(const std::string &text, int width = LABEL_WIDTH);

    /// @brief Generate an On/Off label
    /// @param link boolean function
    /// @param width of label, default of 200
    /// @return
    static UIObject *generateLabelBool(const std::function<bool()>& link, int width = LABEL_WIDTH);

    /// @brief Generate an integer label
    /// @param link integer function
    /// @param width of label, default of 200
    /// @return
    static UIObject *generateLabelInt(const std::function<int()>& link, int width = LABEL_WIDTH);

    /// @brief Generate a clickable button
    /// @param text for the button
    /// @param callback function to run when clicked
    /// @param width width of button, default of 200
    /// @return
    static UIObject *generateButton(const std::string &text, std::function<void()> callback, int width = BUTTON_WIDTH);

protected:
    /// @brief Do nothing, this is only to be used during development as a stub
    static void s_menuToNothing();

    /// @brief Go to previous state by popping state off the stack
    static void s_previousState();
};