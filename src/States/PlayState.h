#pragma once

//Ignore anything that is greyed out, it will be used by the engine

#include "GameObjects/GameObjectCreature/Player.h"
#include "GameObjects/GameObjectCreature/Dog.h"

#include "BaseMap.h"


#include "CommandProcessor.h"

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
    /// @param direction New direction
    void changeMap(const std::string& mapName, float destX, float destY, DIRECTION direction);

    /// Called when the player opts to load a saved game
    static void loadGame();
    /// Called when the player opts to save the game
    static void saveGame();

    /// Scripting engine
    CommandProcessor m_commandProcessor;

    void drawUI() const;
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