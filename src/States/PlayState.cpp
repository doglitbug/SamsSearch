#include "PlayState.h"

void PlayState::onEnter() {
    //GameObjectFactory::get()->registerType("Player", new PlayerCreator());
    GameObjectFactory::get()->registerType("Teleport", new TeleportCreator());
    GameObjectFactory::get()->registerType("Dog", new DogCreator());
    GameObjectFactory::get()->registerType("Cat", new CatCreator());

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

    changeMap("Test", 18 * 32, 2 * 32, SOUTH);
}

void PlayState::update(const float deltaTime) {
    //TODO Only update object layer, at least until we have animations eg for water?
    mPlayer->update(deltaTime, nullptr);
    //TODO All dynamics need to do this?
    mPlayer->checkMapCollision(deltaTime, pCurrentMap->getCollisionLayer()[0]);

    const SDL_FRect playerHitBox = mPlayer->getWorldHitBox();

    //TODO Remove object layer and have only a map of dynamics?
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
                    changeMap(tp->destMap, tp->destX, tp->destY, tp->destDirection);
                    AssetManager::get()->playSound("Enter door");
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
    int x = mPlayer->m_position.getX() - width / 2;
    if (x < 0) x = 0;
    //TODO Fix this
    //if (x > pCurrentMap->getWidth()*32 - width) x = pCurrentMap->getWidth()*32 - width;

    int y = mPlayer->m_position.getY() - height / 2;
    if (y < 0) y = 0;
    //TODO Fix this
    //if (y + height > pCurrentMap->getHeight()) y = pCurrentMap->getHeight() - height;

    return SDL_Rect{x, y, width, height};
}

void PlayState::changeMap(const std::string &mapName, const float destX, const float destY, const DIRECTION direction) {
    //First map
    if (!pCurrentMap) {
        pCurrentMap = m_maps.find(mapName)->second;
        pCurrentMap->onEnter(); //TODO Import GOs

        mPlayer->m_position = Vector2D(destX, destY);
        mPlayer->m_direction = direction;
        return;
    }

    //Check if we are changing to a different map
    if (mapName != pCurrentMap->getFileName()) {
        pCurrentMap->onExit();
        pCurrentMap = m_maps.find(mapName)->second;
        pCurrentMap->onEnter(); //TODO Import GOs
    }

    mPlayer->m_position = Vector2D(destX, destY);
    mPlayer->m_direction = direction;
}

void PlayState::loadGame() {
    //TODO Let this function know which game/file to load
}

void PlayState::saveGame() {
    //TODO Save game state for later loading
};

void PlayState::drawUI() const {
    //TODO Make this better by caching this crap?

    int width, height;
    EngineStateManager::get()->getWindowSize(&width, &height);

    const std::string mapName = pCurrentMap->getName();
    //TODO Make this better by measuring correctly
    const int textWidth = static_cast<int>(mapName.length()) * 32;
    //TODO Overwrite this texture with the new map name on change map...
    //or properly implement writeTextToScreen
    AssetManager::get()->createTextTexture(textWidth, 60, mapName, "Text32", "mapName");
    AssetManager::get()->drawTexture("mapName", width / 2 - textWidth / 2, 0, textWidth, 60);

    //TODO Now that it is drawn, we can delete the texture (it needs to be deleted so that different map names work)
    AssetManager::get()->deleteTexture("mapName");

    //TODO Change this to reference the short name that is the key in the loaded map dictionary
    if (pCurrentMap->getName()=="The outside world") {
        const std::vector<std::string> dialogLines = {
            "Hello",
            " ",
            "Have you been inside yet?",
            "You need to find your shoes",
            "and as usual, turn off your damn light!"
        };

        const sprite dialogFace{"tf_char2", 144, 144};

        const auto dialog = AssetManager::get()->createDialogue("Samuel", dialogFace, dialogLines, "Text");
        AssetManager::get()->drawTexture("dialog", 0, height - 164, width, 164);
        AssetManager::get()->deleteTexture("dialog");
    }
}

void PlayState::handleInput() const {
    if (InputManager::get()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        EngineStateManager::get()->getStateMachine()->pushState("PAUSE");
        return;
    }

    mPlayer->m_velocity = InputManager::get()->getMovement() *= mPlayer->m_speed;
}
