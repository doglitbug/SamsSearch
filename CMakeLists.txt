cmake_minimum_required(VERSION 3.22)
project(SamsSearch)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/ThirdParty/Base64)
include_directories(src/Objects)
include_directories(src/Objects/Menus)
include_directories(src/Levels)
include_directories(src/Managers)
include_directories(src/States)
include_directories(src/ThirdParty/TinyXML)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SamsSearch
        src/ThirdParty/Base64/base64.cpp
        src/ThirdParty/Base64/base64.h
        src/Objects/Menus/Button.cpp
        src/Objects/Menus/Button.h
        src/Objects/Menus/Label.h
        src/Objects/Menus/LabelBoolean.h
        src/Objects/Menus/LabelInteger.h
        src/Objects/Menus/Title.h
        src/Objects/GameObjects/Teleport.cpp
        src/Objects/GameObjects/Teleport.h
        src/Objects/BaseObject.h
        src/Objects/GameObjectFactory.h
        src/Objects/LoaderParams.h
        src/Objects/GameObjects/Player.cpp
        src/Objects/GameObjects/Player.h
        src/Objects/GameObjects/GameObject.cpp
        src/Objects/GameObjects/GameObject.h
        src/Levels/CollisionLayer.cpp
        src/Levels/CollisionLayer.h
        src/Levels/Layer.h
        src/Levels/Level.h
        src/Levels/LevelParser.cpp
        src/Levels/LevelParser.h
        src/Levels/ObjectLayer.cpp
        src/Levels/ObjectLayer.h
        src/Levels/TileLayer.cpp
        src/Levels/TileLayer.h
        src/Managers/AssetManager.cpp
        src/Managers/AssetManager.h
        src/Managers/EngineStateManager.cpp
        src/Managers/EngineStateManager.h
        src/Managers/InputManager.cpp
        src/Managers/InputManager.h
        src/Managers/SettingsManager.cpp
        src/Managers/SettingsManager.h
        src/States/BaseState.h
        src/States/StateMachine.cpp
        src/States/StateMachine.h
        src/States/MainMenuState.cpp
        src/States/MainMenuState.h
        src/States/MenuState.cpp
        src/States/MenuState.h
        src/States/PauseState.cpp
        src/States/PauseState.h
        src/States/PlayState.cpp
        src/States/PlayState.h
        src/States/SettingsState.cpp
        src/States/SettingsState.h
        src/ThirdParty/TinyXML/tinyxml2.cpp
        src/ThirdParty/TinyXML/tinyxml2.h
        src/main.cpp
        src/Vector2D.h
        src/Objects/Menus/UIObject.h
        src/Objects/Menus/UIObject.cpp
        src/Objects/GameObjects/NPC.h
        src/Objects/GameObjects/NPC.cpp
        src/Objects/GameObjects/Dog.cpp
        src/Objects/GameObjects/Dog.h)

find_package(ZLIB)

target_link_libraries(${PROJECT_NAME} SDL3 SDL3_image SDL3_mixer SDL3_ttf ZLIB::ZLIB)
