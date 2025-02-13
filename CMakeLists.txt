cmake_minimum_required(VERSION 3.22)
project(SamsSearch)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/ThirdParty/Base64)
include_directories(src/Objects)
include_directories(src/Objects/UIObjects)
include_directories(src/Maps)
include_directories(src/Managers)
include_directories(src/States)
include_directories(src/ThirdParty/TinyXML)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SamsSearch
        src/ThirdParty/Base64/base64.cpp
        src/ThirdParty/Base64/base64.h
        src/Objects/UIObjects/Button.cpp
        src/Objects/UIObjects/Button.h
        src/Objects/UIObjects/Label.h
        src/Objects/UIObjects/LabelBoolean.h
        src/Objects/UIObjects/LabelInteger.h
        src/Objects/UIObjects/Title.h
        src/Objects/GameObjects/GameObjectItem/Teleport.cpp
        src/Objects/GameObjects/GameObjectItem/Teleport.h
        src/Objects/GameObjects/GameObjectFactory.h
        src/Objects/LoaderParams.h
        src/Objects/GameObjects/GameObjectCreature/Player.cpp
        src/Objects/GameObjects/GameObjectCreature/Player.h
        src/Objects/GameObjects/GameObject.cpp
        src/Objects/GameObjects/GameObject.h
        src/Maps/CollisionLayer.cpp
        src/Maps/CollisionLayer.h
        src/Maps/BaseLayer.h
        src/Maps/BaseMap.h
        src/Maps/MapParser.cpp
        src/Maps/MapParser.h
        src/Maps/GameObjectLayer.cpp
        src/Maps/GameObjectLayer.h
        src/Maps/TileLayer.cpp
        src/Maps/TileLayer.h
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
        src/States/BaseMenuState.cpp
        src/States/BaseMenuState.h
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
        src/Objects/UIObjects/UIObject.h
        src/Objects/UIObjects/UIObject.cpp
        src/Objects/GameObjects/GameObjectCreature/NPC.h
        src/Objects/GameObjects/GameObjectCreature/NPC.cpp
        src/Objects/GameObjects/GameObjectCreature/Dog.cpp
        src/Objects/GameObjects/GameObjectCreature/Dog.h
        src/Maps/Maps/MapTest.cpp
        src/Maps/Maps/MapTest.h
        src/Objects/GameObjects/GameObjectCreature/GameObjectCreature.cpp
        src/Objects/GameObjects/GameObjectCreature/GameObjectCreature.h
        src/Objects/GameObjects/GameObjectItem/GameObjectItem.cpp
        src/Objects/GameObjects/GameObjectItem/GameObjectItem.h
        src/CPO.h)

find_package(ZLIB)

target_link_libraries(${PROJECT_NAME} SDL3 SDL3_image SDL3_mixer SDL3_ttf ZLIB::ZLIB)
