#pragma once

#include "BaseMenuState.h"

class SettingsMenu : public BaseMenuState
{
public:
    SettingsMenu(Settings* pSettings){ m_pSettings = pSettings; }

    void onEnter() override;
    void update(float deltaTime) override;
    void onExit() override;

private:
    Settings* m_pSettings;
    void s_menuTitleMusicOff();
    void s_menuTitleMusicOn();

    void s_menuGameMusicOff();
    void s_menuGameMusicOn();

    void s_menuMusicVolumeDown();
    void s_menuMusicVolumeUp();
    void s_menuGameVolumeDown();
    void s_menuGameVolumeUp();

    void s_menuSaveSettings();
    //TODO Reset settings
    void s_menuResetSettings();

    static constexpr int MUSICVOLUMESCALE = 5;
    static constexpr int GAMEVOLUMESCALE = 5;
};
