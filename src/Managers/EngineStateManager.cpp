#include <iostream>

#include "EngineStateManager.h"
#include "AssetManager.h"
#include "InputManager.h"

#include "../States/MainMenuState.h"
#include "../States/PauseState.h"
#include "../States/PlayState.h"
#include "../States/SettingsState.h"

#include "Objects/GameObjects/GameObjectCreature/Player.h"
#include "Objects/GameObjects/GameObjectItem/Teleport.h"
#include "Objects/GameObjects/GameObjectCreature/NPC.h"
#include "Objects/GameObjects/GameObjectCreature/Dog.h"

#include <algorithm>


bool EngineStateManager::init(const char *title, int width, int height, bool fullscreen)
{
    //Let's load the settings here as we don't know when we will need any of them
    SettingsManager::get()->loadSettings();

    int flags = SDL_WINDOW_RESIZABLE;
    m_scale = 1;
    if (fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;

    // Attempt to initialize SDL
    // TODO Only init subsystems that are needed, for example we couldn't use this on RISC OS on Raspberry Pi as there is no CD-ROM drive!
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL Init fail\n";
        return false;
    }

    // Init the window
    m_pWindow = SDL_CreateWindow(title, width, height, flags);
    if (m_pWindow == nullptr)
    {
        std::cout << "SDL Window init fail\n";
        return false;
    }

    // Create the renderer
    m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL);
    if (m_pRenderer == nullptr) // renderer init success
    {
        std::cout << "SDL Renderer init fail\n";
        return false;
    }

    //Link the render, so we don't need to call the singleton all the time.
    AssetManager::get()->setRenderer(m_pRenderer);

    // Set a drawing scale
    // TODO Option in video m_settings?
    // IF you scale here, everything else needs to account for it, for example MousePosition...
    if (!SDL_SetRenderScale(m_pRenderer, m_scale, m_scale))
    {
        std::cout << "SDL Renderer set scale fail\n";
        return false;
    }

    InputManager::get()->initializeJoysticks();
    InputManager::get()->initializeMouse();


    //TODO Move loading to a startup State? (video etc)
    //Preload assets
    AssetManager::get()->loadFont("PressStart2P-vaV7.ttf", "Text", 16);
    AssetManager::get()->loadFont("PressStart2P-vaV7.ttf", "Header", 64);

    //Load the background textures for the title image
    AssetManager::get()->loadTexture("assets/images/menus/mainlogo.png", "title");

    //Preload toggle text
    AssetManager::get()->createTextTexture(200,50, "On", "Text", "toggle_On");
    AssetManager::get()->createTextTexture(200,50, "Off", "Text", "toggle_Off");

    //Preload integer value text (not loaded elsewhere!)
    for (int i = 0; i <= 100; i += 5) {
        AssetManager::get()->createTextTexture(200, 50, std::to_string(i), "Text", "int_" + std::to_string(i));
    }

    //Preload sprite sheets until we get a better way of doing this:
    AssetManager::get()->loadTexture("assets/images/characters/chara2.png", "character2");
    AssetManager::get()->loadTexture("assets/images/characters/animals1.png", "animals1");

    //Preload main menu audio
    AssetManager::get()->loadMusic("assets/music/chiptunes/CGE-title-theme.flac", "main_menu");
    AssetManager::get()->loadSound("assets/sounds/chiptunes/action-and-game/NFF-glass-breaking.wav", "glass-breaking");

    //Add all states
    m_pGameStateMachine = new StateMachine();

    m_pGameStateMachine->registerState("MAINMENU", new MainMenuState());
    m_pGameStateMachine->registerState("PLAY", new PlayState());

    //TODO Move elsewhere, should this be in the PlayState?
    GameObjectFactory::get()->registerType("Player", new PlayerCreator());
    GameObjectFactory::get()->registerType("NPC", new NPCCreator());
    GameObjectFactory::get()->registerType("Teleport", new TeleportCreator());
    GameObjectFactory::get()->registerType("Dog", new DogCreator());

    m_pGameStateMachine->registerState("PAUSE", new PauseState());
    m_pGameStateMachine->registerState("SETTINGS", new SettingsState());

    m_pGameStateMachine->setInitialState("MAINMENU");
    m_bRunning = true;
    return true;
}

void EngineStateManager::render()
{
    //TODO Set this color in the state?
    SDL_SetRenderDrawColor(m_pRenderer, 25, 25, 25, 255);
    SDL_RenderClear(m_pRenderer);
    m_pGameStateMachine->render();
    SDL_RenderPresent(m_pRenderer);
}

void EngineStateManager::update(float deltaTime)
{
    m_pGameStateMachine->update(deltaTime);
    Vector2D *p_mousePos = InputManager::get()->getMousePosition();
}

void EngineStateManager::handleEvents()
{
    InputManager::get()->update();
}

void EngineStateManager::clean()
{
    std::cout << "Cleaning game\n";

    AssetManager::get()->clean();
    InputManager::get()->clean();
    //SettingsManager::get()->clean();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
