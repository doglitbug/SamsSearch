#include <iostream>

#include "App.h"
#include "Assets.h"
#include "InputManager.h"

#include "../States/MainMenuState.h"
#include "../States/PauseState.h"
#include "../States/PlayState.h"
#include "../States/SettingsMenu.h"

App::App()
{
    //Load settings subsystem here for video init
    m_Settings.load();

    int flags = SDL_WINDOW_RESIZABLE;
    if (m_Settings.getFullScreen())
        flags |= SDL_WINDOW_FULLSCREEN;

    // Attempt to initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        std::cout << "SDL Init fail\n";
        return;
    }

    // Init the window
    //TODO Load res from settings
    m_pWindow = SDL_CreateWindow("Sams Search", 800, 640, flags);
    if (m_pWindow == nullptr)
    {
        std::cout << "SDL Window init fail\n";
        return;
    }

    // Create the renderer
    m_pRenderer = SDL_CreateRenderer(m_pWindow, nullptr);
    if (m_pRenderer == nullptr) // renderer init success
    {
        std::cout << "SDL Renderer init fail\n";
        return;
    }

    // Create assets subsystem
    m_pAssets = new Assets(this) ;

    //TODO Move loading to a startup State? (video etc)
    //Preload assets
    m_pAssets->loadFont("PressStart2P-vaV7.ttf", "Text", 16);
    m_pAssets->loadFont("PressStart2P-vaV7.ttf", "Text32", 32);
    m_pAssets->loadFont("PressStart2P-vaV7.ttf", "Header", 64);

    //Load the background textures for the title image
    m_pAssets->loadTexture("assets/images/menus/mainlogo.png", "title");

    //Preload toggle text
    m_pAssets->createTextTexture(200, 50, "On", "Text", "toggle_On");
    m_pAssets->createTextTexture(200, 50, "Off", "Text", "toggle_Off");

    //Preload integer value text (not loaded elsewhere!)
    for (int i = 0; i <= 100; i += 5)
    {
        m_pAssets->createTextTexture(200, 50, std::to_string(i), "Text", "int_" + std::to_string(i));
    }

    //Preload sprite sheets until we get a better way of doing this:
    m_pAssets->loadTexture("assets/images/characters/chara2.png", "character2");
    m_pAssets->loadTexture("assets/images/characters/tf_char2_MV.png", "tf_char2");
    m_pAssets->loadTexture("assets/images/characters/animals1.png", "animals1");

    //Preload main menu audio
    m_pAssets->loadMusic("assets/music/chiptunes/CGE-title-theme.flac", "main_menu");
    m_pAssets->loadSound("assets/sounds/leohpaz/Inventory/Managing/Unequip.wav", "Menu audio check");

    //Preload other stuff

    //Create input subsystem

    InputManager::get()->initializeGamepads();
    InputManager::get()->initializeMouse();


    //Add all states
    m_pStateMachine = new StateMachine();

    m_pStateMachine->registerState("MAINMENU", new MainMenuState());
    m_pStateMachine->registerState("PLAY", new PlayState());

    m_pStateMachine->registerState("PAUSE", new PauseState());
    m_pStateMachine->registerState("SETTINGS", new SettingsMenu());

    //TODO Delete m_pStateMachine->setInitialState("MAINMENU");
    m_bRunning = true;
}

void App::render() const
{
    //TODO Set this color in the state?
    SDL_SetRenderDrawColor(m_pRenderer, 25, 25, 25, 255);
    SDL_RenderClear(m_pRenderer);
    m_pStateMachine->render();
    SDL_RenderPresent(m_pRenderer);
}

void App::update(float deltaTime) const
{
    m_pStateMachine->update(deltaTime);
}

void App::handleEvents()
{
    InputManager::get()->update();
    //TODO Move this to inputmanager???
    Vector2D* p_mousePos = InputManager::get()->getMousePosition();
}

App::~App()
{
    std::cout << "Cleaning game\n";

    //m_pAssets->clean();
    //InputManager::get()->clean();
    //SettingsManager::get()->clean();
}
