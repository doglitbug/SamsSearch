#include "SettingsState.h"

void SettingsState::onEnter() {
    //Header
    m_gameObjects.push_back(generateHeader("Settings"));
    m_gameObjects.push_back(generateLabel("Title Music", 300));
    m_gameObjects.push_back(generateButton("|<", s_menuTitleMusicOff, 50));
    m_gameObjects.push_back(generateLabel(SettingsManager::getTitleMusicEnabled));
    m_gameObjects.push_back(generateButton(">|", s_menuTitleMusicOn, 50));

    m_gameObjects.push_back(generateLabel("Game Music", 300));
    m_gameObjects.push_back(generateButton("|<", s_menuGameMusicOff, 50));
    m_gameObjects.push_back(generateLabel(SettingsManager::getGameMusicEnabled));
    m_gameObjects.push_back(generateButton(">|", s_menuGameMusicOn, 50));

    m_gameObjects.push_back(generateLabel("Music Volume", 300));
    m_gameObjects.push_back(generateButton("<", s_menuMusicVolumeDown, 50));
    m_gameObjects.push_back(generateLabel(SettingsManager::getMusicVolume));
    m_gameObjects.push_back(generateButton(">", s_menuMusicVolumeUp, 50));

    m_gameObjects.push_back(generateLabel("Game Volume", 300));
    m_gameObjects.push_back(generateButton("<", s_menuGameVolumeDown, 50));
    m_gameObjects.push_back(generateLabel(SettingsManager::getGameVolume));
    m_gameObjects.push_back(generateButton(">", s_menuGameVolumeUp, 50));

    m_gameObjects.push_back(generateButton("Reset", s_menuResetSettings));
    m_gameObjects.push_back(generateButton("Save", s_menuSaveSettings));
    m_gameObjects.push_back(generateButton("Back", s_previousState));
}

void SettingsState::update(float deltaTime) {
    int width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

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

void SettingsState::s_menuTitleMusicOff() {
    SettingsManager::get()->setTitleMusicEnabled(false);
}

void SettingsState::s_menuTitleMusicOn() {
    SettingsManager::get()->setTitleMusicEnabled(true);
}

void SettingsState::s_menuGameMusicOff() {
    SettingsManager::get()->setGameMusicEnabled(false);
}

void SettingsState::s_menuGameMusicOn() {
    SettingsManager::get()->setGameMusicEnabled(true);
}

void SettingsState::s_menuMusicVolumeDown() {
    int value = SettingsManager::getMusicVolume();
    value -= MUSICVOLUMESCALE;
    if (value < 0) { value = 0; }
    SettingsManager::get()->setMusicVolume(value);
}

void SettingsState::s_menuMusicVolumeUp() {
    int value = SettingsManager::getMusicVolume();
    value += MUSICVOLUMESCALE;
    if (value > 100) { value = 100; }
    SettingsManager::get()->setMusicVolume(value);
}

void SettingsState::s_menuGameVolumeDown() {
    int value = SettingsManager::getGameVolume();
    value -= GAMEVOLUMESCALE;
    if (value < 0) { value = 0; }
    SettingsManager::get()->setGameVolume(value);
    AssetManager::get()->playSound("Menu audio check");
}

void SettingsState::s_menuGameVolumeUp() {
    int value = SettingsManager::getGameVolume();
    value += GAMEVOLUMESCALE;
    if (value > 100) { value = 100; }
    SettingsManager::get()->setGameVolume(value);
    AssetManager::get()->playSound("Menu audio check");
}

void SettingsState::s_menuSaveSettings() {
    SettingsManager::get()->saveSettings();
}

void SettingsState::s_menuResetSettings() {
    SettingsManager::get()->resetSettings();
}

void SettingsState::onExit() {
    //TODO Check for need to save m_settings?
    BaseState::onExit();
}
