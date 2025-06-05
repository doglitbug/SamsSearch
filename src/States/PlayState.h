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

    /// Called when the player opts to load a saved game
    void loadGame();
    /// Called when the player opts to save the game
    void saveGame();

    void drawUI();
    void handleInput();

    /// The current map
    BaseMap *pCurrentMap;
    /// All loaded maps
    std::map<std::string, BaseMap *> m_maps;
    /// Current maps gameObjects
    std::vector<GameObject *> m_gameObjects;

    Player *mPlayer;


    /// Get the viewport to draw within (basically camera position)
    SDL_Rect getViewport() const;
};