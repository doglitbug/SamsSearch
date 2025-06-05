#include "PlayState.h"

#include "../Managers/InputManager.h"
#include "GameObjectLayer.h"
#include "GameObjects/GameObjectItem/Teleport.h"
#include "Maps/MapTest.h"
#include "Maps/Maps/MapInsideDadsHouse.h"

void PlayState::onEnter() {
    m_maps["InsideDadsHouse"] = new MapInsideDadsHouse();
    m_maps["Test"] = new MapTest();

    //TODO Determine if we are starting a new game or loading one?
    //Set player position/details from map?
    //TODO Get these defaults from choose character screen/co-ords from map?
    //Create new player
    mPlayer = new Player();

    auto playerProp = std::map<std::string, std::string>();
    playerProp["textureID"] = "character2";
    playerProp["startColumn"] = "0";
    playerProp["startRow"] = "0";

    auto prop = CPO(playerProp);
    mPlayer->load(100, 100, 52, 72, prop);

    changeMap("Test", 18 * 32, 2 * 32);
}

void PlayState::update(float deltaTime) {
    //TODO Only update object layer, at least until we have animations eg for water?
    mPlayer->update(deltaTime, nullptr);
    //TODO All dynamics need to do this?
    mPlayer->checkMapCollision(deltaTime, pCurrentMap->getCollisionLayer()[0]);

    const SDL_FRect playerHitBox = mPlayer->getWorldHitBox();

    for (GameObjectLayer *layer: *pCurrentMap->getObjectLayers()) {
        layer->update(deltaTime, mPlayer);

        for (auto *gameObject: *layer->getGameObjects()) {
            //Check map collision here
            if (const auto goc = dynamic_cast<GameObjectCreature *>(gameObject)) {
                goc->checkMapCollision(deltaTime, pCurrentMap->getCollisionLayer()[0]);
            }
            //TODO Else we are a GO Item?

            //Check intersection with player
            //TODO Change this to all dynamics so they dont over lap
            SDL_FRect otherHitBox = gameObject->getWorldHitBox();
            if (SDL_HasRectIntersectionFloat(&playerHitBox, &otherHitBox)) {
                //TODO IF type of teleport, do xyz else
                if (const auto tp = dynamic_cast<Teleport *>(gameObject)) {
                    changeMap(tp->destMap, tp->destX, tp->destY);
                    continue;
                }
                gameObject->onInteraction(mPlayer, INTERACT_TYPE::TOUCH);
                //else do collision based stuff to stop over lapping
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
    pCurrentMap = nullptr;
    delete (mPlayer);

    for (auto it = m_maps.begin(); it != m_maps.end();) {
        it = m_maps.erase(it); // Returns iterator to the next element
    }
    m_maps.clear();

    BaseState::onExit();
}

SDL_Rect PlayState::getViewport() const {
    int width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

    //Set viewport position for x axis
    int x = mPlayer->getPosition().getX() - width / 2;
    if (x < 0) x = 0;
    //TODO Fix this
    //if (x > pCurrentMap->getWidth()*32 - width) x = pCurrentMap->getWidth()*32 - width;

    int y = mPlayer->getPosition().getY() - height / 2;
    if (y < 0) y = 0;
    //TODO Fix this
    //if (y + height > pCurrentMap->getHeight()) y = pCurrentMap->getHeight() - height;

    return SDL_Rect{x, y, width, height};
}

void PlayState::changeMap(const std::string mapName, float destX, float destY) {
    //First map
    if (!pCurrentMap) {
        pCurrentMap = m_maps.find(mapName)->second;
        pCurrentMap->onEnter(); //TODO Import GOs

        mPlayer->setPosition(Vector2D(destX, destY));
        return;
    }


    //TODO Check if we are changing to current map, probs just a local teleport
    if (mapName.compare(pCurrentMap->getFileName()) != 0) {
        pCurrentMap->onExit();
        pCurrentMap = m_maps.find(mapName)->second;
        pCurrentMap->onEnter(); //TODO Import GOs
    }

    //Else teleport within same Map
    mPlayer->setPosition(Vector2D(destX, destY));
}

void PlayState::loadGame() {
    //TODO Let this function know which game/file to load
}

void PlayState::saveGame() {
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

void PlayState::handleInput() {
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
    if (InputManager::get()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        mPlayer->m_velocity.setX(1);
    } else if (InputManager::get()->isKeyDown(SDL_SCANCODE_LEFT)) {
        mPlayer->m_velocity.setX(-1);
    } else {
        mPlayer->m_velocity.setX(0);
    }

    if (InputManager::get()->isKeyDown(SDL_SCANCODE_DOWN)) {
        mPlayer->m_velocity.setY(1);
    } else if (InputManager::get()->isKeyDown(SDL_SCANCODE_UP)) {
        mPlayer->m_velocity.setY(-1);
    } else {
        mPlayer->m_velocity.setY(0);
    }

    // Pythagoras thou art a heartless bitch
    mPlayer->m_velocity.normalize();
    mPlayer->m_velocity *= mPlayer->speed;
}
