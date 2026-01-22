#pragma once

#include <map>
#include "BaseMenuState.h"
#include "../Subsystems/Settings.h"

class MainMenuState : public BaseMenuState {
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void onExit() override;
private:
    static void s_menuToPlay();
    static void s_menuToSettings();
    static void s_menuToExit();
};