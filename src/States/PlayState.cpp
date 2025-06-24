#include "PlayState.h"

#include <algorithm>

void PlayState::onEnter() {
    //GameObjectFactory::get()->registerType("Player", new PlayerCreator());
    GameObjectFactory::get()->registerType("Teleport", new TeleportCreator());
    GameObjectFactory::get()->registerType("Dog", new DogCreator());
    GameObjectFactory::get()->registerType("Cat", new CatCreator());
    GameObjectFactory::get()->registerType("Sign", new SignCreator());

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
    //CutScene
    if (!m_commandProcessor.UserControl()) {
        m_commandProcessor.ProcessCommands(deltaTime);
        return;
    }

    //TODO Only update object layer, at least until we have animations eg for water?
    mPlayer->update(deltaTime, nullptr);
    //TODO All dynamics need to do this?
    mPlayer->checkMapCollision(deltaTime, pCurrentMap->getCollisionLayer()[0]);

    const SDL_FRect playerHitBox = mPlayer->getWorldHitBox();

    for (auto *gameObject: *pCurrentMap->getGameObjects()) {
        gameObject->update(deltaTime, mPlayer);

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
    for (GameObject *gameObject: *pCurrentMap->getGameObjects()) { gameObject->drawSelf(&pViewport); }
    //Draw player on top of everyone else
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
    //TODO Delete GOs
    BaseState::onExit();
}

SDL_Rect PlayState::getViewport() const {
    int windowWidth, windowHeight;
    EngineStateManager::get()->getWindowSize(&windowWidth, &windowHeight);

    //Set viewport position for-x axis
    const int mapWidth = pCurrentMap->getWidth() * 32;
    int x = mPlayer->m_position.getX() - windowWidth / 2;

    // Clamp the value of x within valid bounds
    if (mapWidth <= windowWidth) {
        x = 0;  // The Map is smaller than or equal to the window
    } else {
        x = std::clamp(x, 0, mapWidth - windowWidth);
    }

    //Set viewport for y-axis
    const int mapHeight = pCurrentMap->getHeight() * 32;
    int y = mPlayer->m_position.getY() - windowHeight / 2;

    // Clamp the value of y within valid bounds
    if (mapHeight <= windowHeight) {
        y = 0;  // The Map is smaller than or equal to the window
    } else {
        y = std::clamp(y, 0, mapHeight - windowHeight);
    }

    return SDL_Rect{x, y, windowWidth, windowHeight};
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

    //Draw Dialog now if we have any.
    //This is placed here to stop it being overwritten on screen!
    if (m_commandProcessor.showingDialog()) {
        EngineStateManager::get()->getWindowSize(&width, &height);
        AssetManager::get()->drawTexture("dialog", 0, height - 164, width, 164);
    }
}

void PlayState::handleInput() {
    if (InputManager::get()->getKeyDown(SDL_SCANCODE_ESCAPE) || InputManager::get()->getButtonDown(SDL_GAMEPAD_BUTTON_START)) {
        EngineStateManager::get()->getStateMachine()->pushState("PAUSE");
        return;
    }

    if (InputManager::get()->getKeyDown(SDL_SCANCODE_Z)) {
        const std::vector<std::string> dialogLines = {
            "Hello",
            "Have you been inside yet?",
            "You need to find your shoes",
            "and as usual, turn off your damn light!",
            "Press A to continue"
        };

        const Sprite dialogFace{"tf_char2", 144, 144};

        m_commandProcessor.AddCommand(new cmdShowDialog(dialogFace, dialogLines));
        m_commandProcessor.AddCommand(new cmdWait(2.5));
    }

    mPlayer->m_velocity = InputManager::get()->getMovement() *= mPlayer->m_speed;
}
