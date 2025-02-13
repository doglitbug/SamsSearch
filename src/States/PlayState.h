#pragma once

#include <iostream>
#include "Objects/GameObjects/GameObjectCreature/Player.h"

#include "BaseState.h"
#include "BaseMap.h"

#include "Maps/Maps/MapTest.h"

/// @brief PlayState is the GameEngine
class PlayState : public BaseState
{
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void render() override;
    void onExit() override;

private:
    //TODO Direction?
    void changeMap(std::string mapName, float destX, float destY);
    void loadGame();
    void saveGame();
    void drawUI();
    void handleInput();

    BaseMap *pCurrentMap;
    /// @brief Get the viewport to draw within (basically camera position)
    SDL_Rect getViewport();

    Player *mPlayer;

    //TODO Move
};