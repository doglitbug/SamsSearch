#include "SettingsMenu.h"
#include <functional>

void SettingsMenu::onEnter() {
    //Header
    m_gameObjects.push_back(generateHeader("Settings"));

    m_gameObjects.push_back(generateLabel("Title Music", 300));
    m_gameObjects.push_back(generateButton("|<", [this] { s_menuTitleMusicOff(); }, 40));
    m_gameObjects.push_back(generateLabelBool([this]()->bool{ return m_pSettings->getTitleMusicEnabled();}));
    m_gameObjects.push_back(generateButton(">|", [this]{s_menuTitleMusicOn();}, 40));

    m_gameObjects.push_back(generateLabel("Title Music Volume", 300));
    m_gameObjects.push_back(generateButton("<",[this]{ s_menuTitleMusicVolumeDown();}, 40));
    m_gameObjects.push_back(generateLabelInt([this]()->int{ return m_pSettings->getTitleMusicVolume();}));
    m_gameObjects.push_back(generateButton(">", [this]{s_menuTitleMusicVolumeUp();}, 40));

    m_gameObjects.push_back(generateLabel("Game Music", 300));
    m_gameObjects.push_back(generateButton("|<", [this]{s_menuGameMusicOff();}, 40));
    m_gameObjects.push_back(generateLabelBool([this]()->bool{ return m_pSettings->getGameMusicEnabled();}));
    m_gameObjects.push_back(generateButton(">|", [this]{s_menuGameMusicOn();}, 40));

    m_gameObjects.push_back(generateLabel("Game Music Volume", 300));
    m_gameObjects.push_back(generateButton("<",[this]{ s_menuGameMusicVolumeDown();}, 40));
    m_gameObjects.push_back(generateLabelInt([this]()->int{ return m_pSettings->getGameMusicVolume();}));
    m_gameObjects.push_back(generateButton(">", [this]{s_menuGameMusicVolumeUp();}, 40));

    m_gameObjects.push_back(generateLabel("Game Volume", 300));
    m_gameObjects.push_back(generateButton("<", [this]{s_menuGameVolumeDown();}, 40));
    m_gameObjects.push_back(generateLabelInt([this]()->int{ return m_pSettings->getGameVolume();}));
    m_gameObjects.push_back(generateButton(">", [this]{s_menuGameVolumeUp();}, 40));

    m_gameObjects.push_back(generateButton("Reset", [this]{s_menuResetSettings();}));
    m_gameObjects.push_back(generateButton("Save", [this]{s_menuSaveSettings();}));
    m_gameObjects.push_back(generateButton("Back", s_previousState));
}

void SettingsMenu::update(float deltaTime) {
    int width, height;
    App::get()->getWindowSize(&width, &height);

    int leftSide = width / 2;
    int middle = 100;

    //Reposition all game objects
    int index = 0;
    int line = 0;
    //Header
    m_gameObjects[index++]->setPosition(leftSide - 350, middle - 100);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + (ROW_HEIGHT + ROW_GAP) * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + (ROW_HEIGHT + ROW_GAP) * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + (ROW_HEIGHT + ROW_GAP) * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + (ROW_HEIGHT + ROW_GAP) * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 50, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 100, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 300, middle + (ROW_HEIGHT + ROW_GAP) * line);

    line++;
    m_gameObjects[index++]->setPosition(leftSide - 350, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide - 100, middle + (ROW_HEIGHT + ROW_GAP) * line);
    m_gameObjects[index++]->setPosition(leftSide + 150, middle + (ROW_HEIGHT + ROW_GAP) * line);

    BaseMenuState::update(deltaTime);
}

void SettingsMenu::s_menuTitleMusicOff()
{
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

void SettingsMenu::s_menuTitleMusicVolumeDown() {
    int value = m_pSettings->getTitleMusicVolume();
    value -= MUSICVOLUMESCALE;
    if (value < 0) { value = 0; }
    m_pSettings->setTitleMusicVolume(value);
}

void SettingsMenu::s_menuTitleMusicVolumeUp() {
    int value = m_pSettings->getTitleMusicVolume();
    value += MUSICVOLUMESCALE;
    if (value > 100) { value = 100; }
    m_pSettings->setTitleMusicVolume(value);
}

void SettingsMenu::s_menuGameMusicVolumeDown() {
    int value = m_pSettings->getGameMusicVolume();
    value -= MUSICVOLUMESCALE;
    if (value < 0) { value = 0; }
    m_pSettings->setGameMusicVolume(value);
}

void SettingsMenu::s_menuGameMusicVolumeUp() {
    int value = m_pSettings->getGameMusicVolume();
    value += MUSICVOLUMESCALE;
    if (value > 100) { value = 100; }
    m_pSettings->setGameMusicVolume(value);
}

void SettingsMenu::s_menuGameVolumeDown() {
    int value = m_pSettings->getGameVolume();
    value -= GAMEVOLUMESCALE;
    if (value < 0) { value = 0; }
    m_pSettings->setGameVolume(value);
    App::get()->getAssets()->playSound("Menu audio check");
}

void SettingsMenu::s_menuGameVolumeUp() {
    int value = m_pSettings->getGameVolume();
    value += GAMEVOLUMESCALE;
    if (value > 100) { value = 100; }
    m_pSettings->setGameVolume(value);
    App::get()->getAssets()->playSound("Menu audio check");
}

void SettingsMenu::s_menuSaveSettings() {
    m_pSettings->save();
}

void SettingsMenu::s_menuResetSettings() {
    m_pSettings->reset();
}

void SettingsMenu::onExit() {
    BaseState::onExit();
}
