#pragma once

#include "Objects/GameObjects/GameObjectCreature/Player.h"

#include "BaseState.h"
#include "BaseMap.h"

/// @brief PlayState is the GameEngine
class PlayState : public BaseState
{
public:
    void onEnter() override;
    void update(float deltaTime) override;
    void render() override;
    void onExit() override;

private:
    /// Move the player to a different map
    /// @param mapName Map to move to
    /// @param destX New x location
    /// @param destY New y location
    /// @todo Direction or assume South?
    void changeMap(std::string mapName, float destX, float destY);

    void loadGame();
    void saveGame();
    void drawUI();
    void handleInput();

    BaseMap *pCurrentMap;

    /// @brief Get the viewport to draw within (basically camera position)
    SDL_Rect getViewport();

    std::map<std::string, BaseMap *> m_maps;

    Player *mPlayer;
};