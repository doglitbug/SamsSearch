cmake_minimum_required(VERSION 3.22)
project(SamsSearch LANGUAGES CXX)

# Use standard variables and prevent global pollution
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure output directories cleanly
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Find required dependencies
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(ZLIB REQUIRED)

# 1. Automatically collect all source and header files recursively
file(GLOB_RECURSE PROJECT_SOURCES 
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# 2. Define the executable target
add_executable(SamsSearch ${PROJECT_SOURCES})

# 3. Modern target-based include paths (Replaces all include_directories)
target_include_directories(SamsSearch PRIVATE 
    src
    src/ThirdParty/Base64
    src/ThirdParty/TinyXML
    src/Objects/GameObjects
    src/Objects/UIObjects
    src/Maps
    src/CutScenes
    src/Subsystems
    src/States
)

# 4. Link libraries directly to the target
target_link_libraries(SamsSearch PRIVATE 
    SDL3::SDL3 
    SDL3_image::SDL3_image 
    SDL3_mixer::SDL3_mixer 
    SDL3_ttf::SDL3_ttf 
    ZLIB::ZLIB
)
