#pragma once

#include <iostream>
#include "Objects/GameObjects/Player.h"

#include "BaseState.h"
#include "BaseMap.h"

#include "MapTest.h"

/// @brief PLayState is the GameEngine
class PlayState : public BaseState
{
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void render() override;
    void onExit() override;

private:
    void loadMap();
    void loadGame();
    void drawUI();
    void handleInput();

    BaseMap *pCurrentMap;
    /// @brief Get the viewport to draw within (basically camera position)
    SDL_Rect getViewport();

    Player *mPlayer;

    //TODO Move
};