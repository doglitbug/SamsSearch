#pragma once

#include <iostream>
#include "BaseMenuState.h"
#include "../Managers/SettingsManager.h"

class SettingsState : public BaseMenuState {
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void onExit() override;
private:

    static void s_menuTitleMusicOff();

    static void s_menuTitleMusicOn();

    static void s_menuGameMusicOff();

    static void s_menuGameMusicOn();

    static void s_menuMusicVolumeDown();

    static void s_menuMusicVolumeUp();

    static void s_menuGameVolumeDown();

    static void s_menuGameVolumeUp();

    static void s_menuSaveSettings();

    static void s_menuResetSettings();

   static constexpr int MUSICVOLUMESCALE = 5;
   static constexpr int GAMEVOLUMESCALE = 5;
};