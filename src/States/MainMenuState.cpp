#include "MainMenuState.h"

void MainMenuState::onEnter() {
    if (SettingsManager::get()->getTitleMusicEnabled()) {
        AssetManager::get()->playMusic("main_menu");
    }
    //Title
    m_gameObjects.push_back(generateTitle());
    //Buttons
    m_gameObjects.push_back(generateButton("New Game", s_menuToPlay));
    m_gameObjects.push_back(generateButton("Load Game", s_menuToNothing));
    m_gameObjects.push_back(generateButton("Settings", s_menuToSettings));
    m_gameObjects.push_back(generateButton("Credits", s_menuToNothing));
    m_gameObjects.push_back(generateButton("Quit", s_menuToExit));
}

void MainMenuState::update(float deltaTime) {
    int width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

    int leftSide = width / 2;
    int middle = 200;

    //Reposition all game objects
    int index = 0;
    int line = 0;
    //Title
    m_gameObjects[index++]->setPosition(leftSide - 453, middle - 100);
    middle += 50;//Lower for large title
    //Buttons
    m_gameObjects[index++]->setPosition(leftSide - 100, middle + 75 * line++);
    m_gameObjects[index++]->setPosition(leftSide - 100, middle + 75 * line++);
    m_gameObjects[index++]->setPosition(leftSide - 100, middle + 75 * line++);
    m_gameObjects[index++]->setPosition(leftSide - 100, middle + 75 * line++);
    m_gameObjects[index++]->setPosition(leftSide - 100, middle + 75 * line++);

    BaseMenuState::update(deltaTime);
}

void MainMenuState::onExit() {
    AssetManager::get()->stopMusic();
    BaseState::onExit();
}

void MainMenuState::s_menuToPlay() {
    EngineStateManager::get()->getStateMachine()->changeState("PLAY");
}

void MainMenuState::s_menuToSettings() {
    EngineStateManager::get()->getStateMachine()->pushState("SETTINGS");
}

void MainMenuState::s_menuToExit() {
    EngineStateManager::get()->quit();
}
