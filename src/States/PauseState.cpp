#include "PauseState.h"

 void PauseState::onEnter() {
    m_gameObjects.push_back(generateHeader("Pause"));

    m_gameObjects.push_back(generateButton("Resume", s_previousState));
    m_gameObjects.push_back(generateButton("Settings", s_pauseToSettings));
    m_gameObjects.push_back(generateButton("Main Menu", s_pauseToMainMenu));
}

void PauseState::update(float deltaTime){
    int width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

    int leftSide = width / 2;
    int middle = 200;

    //Reposition all game objects
    int index = 0;

    //Header
    m_gameObjects[index++]->setPosition(leftSide - HEADER_WIDTH / 2, middle - 100);

    leftSide -= LABEL_WIDTH / 2;
    //Buttons
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);
    m_gameObjects[index++]->setPosition(leftSide, middle + (ROW_HEIGHT + ROW_GAP) * index);

    BaseMenuState::update(deltaTime);
}

void PauseState::onExit() {
    BaseState::onExit();
}

void PauseState::s_pauseToMainMenu() {
    EngineStateManager::get()->getStateMachine()->changeState("MAINMENU");
}

//TODO Combine with menu to m_settings?
void PauseState::s_pauseToSettings() {
    EngineStateManager::get()->getStateMachine()->pushState("SETTINGS");
}
