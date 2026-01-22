#include "MainMenuState.h"

void MainMenuState::onEnter() {
    if (Settings::getTitleMusicEnabled()) {
        Assets::get()->playMusic("main_menu");
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
    App::getSettings()->getWindowSize(&width, &height);

    int leftSide = width / 2;
    int middle = 200;

    //Reposition all game objects
    int index = 0;

    //Title
    m_gameObjects[index++]->setPosition(leftSide - 453, middle - 100);

    leftSide -= LABEL_WIDTH / 2;
    //Buttons
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);

    BaseMenuState::update(deltaTime);
}

void MainMenuState::onExit() {
    Assets::get()->stopMusic();
    BaseState::onExit();
}

void MainMenuState::s_menuToPlay() {
    App::get()->getStateMachine()->changeState("PLAY");
}

void MainMenuState::s_menuToSettings() {
    App::get()->getStateMachine()->pushState("SETTINGS");
}

void MainMenuState::s_menuToExit() {
    App::get()->quit();
}
