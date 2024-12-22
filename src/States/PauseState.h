#pragma once

#include <iostream>
#include "MenuState.h"

class PauseState : public MenuState {
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void onExit() override;
private:
    static void s_pauseToMainMenu();
    static void s_pauseToSettings();
};