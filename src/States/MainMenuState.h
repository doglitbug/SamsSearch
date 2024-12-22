#pragma once

#include <map>
#include "MenuState.h"
#include "../Managers/SettingsManager.h"

class MainMenuState : public MenuState {
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void onExit() override;
private:
    static void s_menuToPlay();
    static void s_menuToSettings();
    static void s_menuToExit();
};