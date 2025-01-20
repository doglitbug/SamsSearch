#pragma once

#include <iostream>
#include "BaseMenuState.h"

class PauseState : public BaseMenuState {
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void onExit() override;
private:
    static void s_pauseToMainMenu();
    static void s_pauseToSettings();
};