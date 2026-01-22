#include <iostream>
#include <fstream>

#include "Settings.h"
#include "Assets.h"

Settings::Settings()
{
    load();
}

void Settings::load()
{
    //TODO Refactor these into an object for RAII
    //TODO Maybe a try catch and load defaults if error?
    std::ifstream inFile;

    //Get file location
    char* filepath = SDL_GetPrefPath("0x00101010", "SamsSearch");

    inFile.open(std::string(filepath) + "settings", std::ios::binary);

    if (inFile)
    {
        //TODO Catch any errors?
        inFile.read(reinterpret_cast<char*>(&m_settings), sizeof(m_settings));
    }
    else
    {
        reset();
    }

    inFile.close();
    SDL_free(filepath);

    //Go tell Asset manager about music stuff
    Assets::get()->setMusicVolume(m_settings.musicVolume);
    Assets::get()->setGameVolume(m_settings.gameVolume);
}

void Settings::save()
{
    //TODO Refactor these into an object for RAII
    std::ofstream outFile;

    //Get file location
    char* filepath = SDL_GetPrefPath("0x00101010", "SamsSearch");

    outFile.open(std::string(filepath) + "settings", std::ios::binary);

    if (outFile)
    {
        outFile.write(reinterpret_cast<char*>(&m_settings), sizeof(m_settings));
    }
    else
    {
        std::cout << "Error writing to file" << std::endl;
    }

    outFile.close();
    SDL_free(filepath);
}

void Settings::reset()
{
    setTitleMusicEnabled(true);
    setGameMusicEnabled(true);
    setMusicVolume(50);
    setGameVolume(75);
    setFullScreen(false);
}

// region Audio
bool Settings::getTitleMusicEnabled() const { return m_settings.titleMusicEnabled; }
void Settings::setTitleMusicEnabled(const bool enabled)
{
    m_settings.titleMusicEnabled = enabled;
    if (!enabled) Assets::get()->stopTitleMusic();
}

bool Settings::getGameMusicEnabled() const { return m_settings.gameMusicEnabled; };
void Settings::setGameMusicEnabled(const bool enabled) { m_settings.gameMusicEnabled = enabled; }

int Settings::getMusicVolume() const { return m_settings.musicVolume; };
void Settings::setMusicVolume(const int volume)
{
    m_settings.musicVolume = volume;
    Assets::get()->setMusicVolume(volume);
};

int Settings::getGameVolume() const { return m_settings.gameVolume; };
void Settings::setGameVolume(const int volume)
{
    m_settings.gameVolume = volume;
    Assets::get()->setGameVolume(volume);
};
// endregion

// region Video
bool Settings::getFullScreen() const { return m_settings.fullScreen; };
void Settings::setFullScreen(const bool enabled) { m_settings.fullScreen = enabled; }
// endregion