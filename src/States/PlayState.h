#pragma once

#include <iostream>
#include "BaseState.h"
#include "Level.h"
#include "Objects/GameObjects/Player.h"

class PlayState : public BaseState
{
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void render() override;
    void onExit() override;

private:
    void newGame();
    void loadGame();
    void drawUI();
    void handleInput();

    Level *pCurrentLevel;
    /// @brief Get the viewport to draw within (basically camera position)
    SDL_Rect getViewport();

    Player *mPlayer;
};