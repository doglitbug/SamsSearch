#pragma once

#include "BaseMenuState.h"

class SettingsMenu : public BaseMenuState
{
public:
    SettingsMenu()= default;

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
    //TODO Reset settings
    static void s_menuResetSettings();

    static constexpr int MUSICVOLUMESCALE = 5;
    static constexpr int GAMEVOLUMESCALE = 5;
};
