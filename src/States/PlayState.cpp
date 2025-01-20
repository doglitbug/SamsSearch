#include "PlayState.h"

#include "../Managers/InputManager.h"
#include "../Levels/LevelParser.h"
#include "ObjectLayer.h"

void PlayState::onEnter() {
    //TODO Determine if we are starting a new game or loading one?
    newGame();
}

void PlayState::update(float deltaTime) {
    BaseState::update(deltaTime);

    //TODO Only update object layer, at least until we have animations eg for water?
    mPlayer->update(deltaTime);
    SDL_FRect *playerHitBox = mPlayer->getWorldHitBox();
    for (ObjectLayer *layer: *pCurrentLevel->getObjectLayers()) {
        layer->update(deltaTime);
        for(auto *gameObject: *layer->getGameObjects()){
            //Check intersection with player
            SDL_FRect *otherHitBox = gameObject->getWorldHitBox();
            if (SDL_HasRectIntersectionFloat(playerHitBox, otherHitBox)) {
                gameObject->onInteraction(mPlayer, INTERACT_TYPE::TOUCH);
            }
            delete otherHitBox;
        }
    }
    delete playerHitBox;

    handleInput();
}

void PlayState::render() {
    SDL_Rect pViewport = getViewport();
    //Draw level
    //TODO render in order:

    //1. Lower layers
    //2. Object layer
    //3. Player
    //4. Upper layers
    //5. Ghost outline of player if required?
    //6. Ignore collision layer

    for (Layer *layer: *pCurrentLevel->getLowerLayers()) { layer->render(&pViewport); }
    for (Layer *layer: *pCurrentLevel->getObjectLayers()) { layer->render(&pViewport); }
    mPlayer->drawAt(&pViewport);
    for (Layer *layer: *pCurrentLevel->getUpperLayers()) { layer->render(&pViewport); }

    drawUI();
    mPlayer->drawHitBox(&pViewport);
    BaseState::render();//?
}

void PlayState::onExit() {
    //TODO Ask to save here as we would only be exiting to the main menu
    delete (pCurrentLevel);
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
    //if (x > pCurrentLevel->getWidth()*32 - width) x = pCurrentLevel->getWidth()*32 - width;

    y = mPlayer->getPosition().getY() - height / 2;
    if (y < 0) y = 0;
    //TODO Fix this
    //if (y + height > pCurrentLevel->getHeight()) y = pCurrentLevel->getHeight() - height;

    return SDL_Rect{x, y, width, height};
}

void PlayState::newGame() {
    //Create new player

    mPlayer = new Player();

    //Load all levels?
    LevelParser levelParser{};

    //TODO Make this a vector
    pCurrentLevel = levelParser.parseLevel("assets/maps/Temp.tmx");

    //Set player position/details from map?
    //TODO Get these defaults from choose character screen/co-ords from map?
    mPlayer->load(LoaderParams(100, 100, 52, 72, "character2", 0, 0));
    mPlayer->setCollisionLayer(pCurrentLevel->getCollisionLayer());
}

void PlayState::loadGame() {
    //TODO Let this function know which game/file to load
}

void PlayState::drawUI() {
    //TODO Make this better by caching this crap?

    int width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

    std::string mapName = pCurrentLevel->getName();
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