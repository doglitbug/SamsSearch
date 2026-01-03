#include "Commands.h"

#include "InputManager.h"

//Show Dialog
cmdShowDialog::cmdShowDialog(const Sprite &dialogFace, const std::vector<std::string> &dialogLines) {
    sprite = dialogFace;
    dialog = dialogLines;
}

void cmdShowDialog::start() {
    AssetManager::get()->createDialogue("Samuel", sprite, dialog, "Text");
}

void cmdShowDialog::update(float deltaTime) {
    //TODO If player hits action button
    if (InputManager::get()->getKeyDown(SDL_SCANCODE_ESCAPE) || InputManager::get()->getButtonDown(SDL_GAMEPAD_BUTTON_SOUTH)) {
        completed = true;
        AssetManager::get()->deleteTexture("dialog");
    }
}

//Wait
cmdWait::cmdWait(const float duration) {
    m_duration = std::max(duration, 0.0f);
    m_timeSoFar = 0.0f;
}

void cmdWait::update(const float deltaTime) {
    m_timeSoFar += deltaTime;

    if (m_timeSoFar >= m_duration) {
        completed = true;
    }
}


//MoveTo
cmdMoveTo::cmdMoveTo(GameObject *gameObjectCreature, const float x, const float y, const float duration) {
    m_gameObject = gameObjectCreature;
    m_endPosition = {x, y};
    m_duration = duration;
    m_timeSoFar = 0.0f;
}

void cmdMoveTo::start() {
    m_endPosition = m_gameObject->m_position;
}

void cmdMoveTo::update(float deltaTime) {
    //TODO https://youtu.be/AWY_ITpldRk?si=HdrVlB860B0IX70H&t=2198
}

//
