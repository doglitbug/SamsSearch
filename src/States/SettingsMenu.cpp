#include "SettingsMenu.h"

void SettingsMenu::linkSettings(Settings* pSettings)
{
    m_pSettings = pSettings;
}

void SettingsMenu::onEnter() {
    //Header
    m_gameObjects.push_back(generateHeader("Settings"));
    m_gameObjects.push_back(generateLabel("Title Music", 300));
    m_gameObjects.push_back(generateButton("|<", s_menuTitleMusicOff, 50));
    m_gameObjects.push_back(generateLabel(m_pSettings->getTitleMusicEnabled()));
    m_gameObjects.push_back(generateButton(">|", s_menuTitleMusicOn, 50));

    m_gameObjects.push_back(generateLabel("Game Music", 300));
    m_gameObjects.push_back(generateButton("|<", s_menuGameMusicOff, 50));
    m_gameObjects.push_back(generateLabel(m_pSettings->getGameMusicEnabled()));
    m_gameObjects.push_back(generateButton(">|", s_menuGameMusicOn, 50));

    m_gameObjects.push_back(generateLabel("Music Volume", 300));
    m_gameObjects.push_back(generateButton("<", s_menuMusicVolumeDown, 50));
    m_gameObjects.push_back(generateLabel(m_pSettings->getMusicVolume()));
    m_gameObjects.push_back(generateButton(">", s_menuMusicVolumeUp, 50));

    m_gameObjects.push_back(generateLabel("Game Volume", 300));
    m_gameObjects.push_back(generateButton("<", s_menuGameVolumeDown, 50));
    m_gameObjects.push_back(generateLabel(m_pSettings->getGameVolume()));
    m_gameObjects.push_back(generateButton(">", s_menuGameVolumeUp, 50));

    m_gameObjects.push_back(generateButton("Reset", s_menuResetSettings));
    m_gameObjects.push_back(generateButton("Save", s_menuSaveSettings));
    m_gameObjects.push_back(generateButton("Back", s_previousState));
}

void SettingsMenu::update(float deltaTime) {
    int width, height;
    App::get()->getWindowSize(&width, &height);

    int leftSide = width / 2;
    int middle = 200;

    //Reposition all game objects
    int index = 0;
    int line = 0;
    //Header
    m_gameObjects[index++]->setPosition(leftSide - 350, middle - 100);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + 75 * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + 75 * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + 75 * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + 75 * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide - 100, middle + 75 * line);
    m_gameObjects[index++]->setPosition(leftSide + 150, middle + 75 * line);

    BaseMenuState::update(deltaTime);
}

void SettingsMenu::s_menuTitleMusicOff() {
    m_pSettings->setTitleMusicEnabled(false);
}

void SettingsMenu::s_menuTitleMusicOn() {
    m_pSettings->setTitleMusicEnabled(true);
}

void SettingsMenu::s_menuGameMusicOff() {
    m_pSettings->setGameMusicEnabled(false);
}

void SettingsMenu::s_menuGameMusicOn() {
    m_pSettings->setGameMusicEnabled(true);
}

void SettingsMenu::s_menuMusicVolumeDown() {
    int value = m_pSettings->getMusicVolume();
    value -= MUSICVOLUMESCALE;
    if (value < 0) { value = 0; }
    m_pSettings->setMusicVolume(value);
}

void SettingsMenu::s_menuMusicVolumeUp() {
    int value = m_pSettings->getMusicVolume();
    value += MUSICVOLUMESCALE;
    if (value > 100) { value = 100; }
    m_pSettings->setMusicVolume(value);
}

void SettingsMenu::s_menuGameVolumeDown() {
    int value = m_pSettings->getGameVolume();
    value -= GAMEVOLUMESCALE;
    if (value < 0) { value = 0; }
    m_pSettings->setGameVolume(value);
    Assets::get()->playSound("Menu audio check");
}

void SettingsMenu::s_menuGameVolumeUp() {
    int value = m_pSettings->getGameVolume();
    value += GAMEVOLUMESCALE;
    if (value > 100) { value = 100; }
    m_pSettings->setGameVolume(value);
    Assets::get()->playSound("Menu audio check");
}

void SettingsMenu::s_menuSaveSettings() {
    m_pSettings->save();
}

void SettingsMenu::s_menuResetSettings() {
    m_pSettings->reset();
}

void SettingsMenu::onExit() {
    //TODO Check for need to save m_settings?
    BaseState::onExit();
}
