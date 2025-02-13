#include "PlayState.h"

#include "../Managers/InputManager.h"
#include "../Maps/MapParser.h"
#include "GameObjectLayer.h"

void PlayState::onEnter() {
    //TODO Determine if we are starting a new game or loading one?
    //Set player position/details from map?
    //TODO Get these defaults from choose character screen/co-ords from map?
    //Create new player
    mPlayer = new Player();
    mPlayer->load(LoaderParams(100, 100, 52, 72, "character2", 0, 0));

    changeMap("Test");
}

void PlayState::update(float deltaTime) {

    //TODO Only update object layer, at least until we have animations eg for water?
    mPlayer->update(deltaTime);
    //TODO All dynamics need to do this?
    mPlayer->checkMapCollision(deltaTime, pCurrentMap->getCollisionLayer()[0]);

    const SDL_FRect playerHitBox = mPlayer->getWorldHitBox();

    for (GameObjectLayer *layer: *pCurrentMap->getObjectLayers()) {
        layer->update(deltaTime, mPlayer);

        for(auto *gameObject: *layer->getGameObjects()){
            //Check map collision here
            if(auto goc = dynamic_cast<GameObjectCreature*>(gameObject)){
                goc->checkMapCollision(deltaTime, pCurrentMap->getCollisionLayer()[0]);
            }

            //Check intersection with player
            SDL_FRect otherHitBox = gameObject->getWorldHitBox();
            if (SDL_HasRectIntersectionFloat(&playerHitBox, &otherHitBox)) {
                gameObject->onInteraction(mPlayer, INTERACT_TYPE::TOUCH);
            }
        }
    }

    //TODO Disable if in cutscene
    handleInput();
}

void PlayState::render() {
    SDL_Rect pViewport = getViewport();
    //Draw level
    //Render in order:

    //1. Lower layers
    //2. Object layer
    //3. Player
    //4. Upper layers
    //5. Ghost outline of player if required?
    //6. Ignore collision layer

    for (BaseLayer *layer: *pCurrentMap->getLowerLayers()) { layer->render(&pViewport); }
    for (BaseLayer *layer: *pCurrentMap->getObjectLayers()) { layer->render(&pViewport); }
    //Draw player on top of everyone!
    mPlayer->drawSelf(&pViewport);
    for (BaseLayer *layer: *pCurrentMap->getUpperLayers()) { layer->render(&pViewport); }

    drawUI();
}

void PlayState::onExit() {
    //TODO Ask to save here as we would only be exiting to the main menu
    delete (pCurrentMap);
    delete (mPlayer);
    BaseState::onExit();
}

SDL_Rect PlayState::getViewport() {
    int x, y, width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

    //Set viewport position for x axis
    x = mPlayer->getPosition().getX() - width / 2;
    if (x < 0) x = 0;
    //TODO Fix this
    //if (x > pCurrentMap->getWidth()*32 - width) x = pCurrentMap->getWidth()*32 - width;

    y = mPlayer->getPosition().getY() - height / 2;
    if (y < 0) y = 0;
    //TODO Fix this
    //if (y + height > pCurrentMap->getHeight()) y = pCurrentMap->getHeight() - height;

    return SDL_Rect{x, y, width, height};
}

void PlayState::changeMap(const std::string mapName) {
    if(pCurrentMap) {
        //TODO delete current map, GOs etc
    }

    MapParser levelParser{};

    pCurrentMap = new MapTest();
    levelParser.parseMap(pCurrentMap);
}

void PlayState::loadGame() {
    //TODO Let this function know which game/file to load
}

void PlayState::saveGame(){
    //TODO Save game state for later loading
};

void PlayState::drawUI() {
    //TODO Make this better by caching this crap?

    int width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

    std::string mapName = pCurrentMap->getName();
    //TODO Make this better by measuring correctly
    int textWidth = (int) mapName.length() * 16;
    //TODO Overwrite this texture with the new map name on change map...
    //or properly implement writeTextToScreen
    AssetManager::get()->createTextTexture(textWidth, 30, mapName, "Text", "mapName");
    AssetManager::get()->drawTexture("mapName", width / 2 - textWidth / 2, 0, 0, 0);

}

void PlayState::handleInput()
{
    if (InputManager::get()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        EngineStateManager::get()->getStateMachine()->pushState("PAUSE");
        return;
    }

    // Movement
    // Joysticks
    /**
    if (InputManager::get()->joysticksInitialised()) {
        m_velocity.setX(InputManager::get()->xValue(0, 1));
        m_velocity.setY(InputManager::get()->yValue(0, 1));
    }
*/

    //TODO Set velocity to zero first?
    //TODO Move all this to InputManager so that we just get the movement vector back and dont need to know about SDL Scan codes
    if (InputManager::get()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        mPlayer->m_velocity.setX(1);
    }
    else if (InputManager::get()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        mPlayer->m_velocity.setX(-1);
    }
    else
    {
        mPlayer->m_velocity.setX(0);
    }

    if (InputManager::get()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        mPlayer->m_velocity.setY(1);
    }
    else if (InputManager::get()->isKeyDown(SDL_SCANCODE_UP))
    {
        mPlayer->m_velocity.setY(-1);
    }
    else
    {
        mPlayer->m_velocity.setY(0);
    }

    // Pythagoras thou art a heartless bitch
    mPlayer->m_velocity.normalize();
    mPlayer->m_velocity *= mPlayer->speed;
}