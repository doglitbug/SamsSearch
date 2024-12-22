#include <iostream>
#include <fstream>
#include "SettingsManager.h"

void SettingsManager::loadSettings() {
    //TODO Refactor these into an object for RAII
    std::ifstream inFile;

    //Get file location
    char *filepath = SDL_GetPrefPath("0x00101010", "SamsSearch");

    inFile.open(std::string(filepath) + "settings", std::ios::binary);

    if (inFile) {
        //TODO Catch any errors?
        inFile.read((char *) &m_settings, sizeof(m_settings));
    } else {
        resetSettings();
    }

    inFile.close();
    SDL_free(filepath);

    //Go tell Asset manager about music stuff
    AssetManager::get()->setMusicVolume(m_settings.musicVolume);
    AssetManager::get()->setGameVolume(m_settings.gameVolume);
}

void SettingsManager::saveSettings() {
    //TODO Refactor these into an object for RAII
    std::ofstream outFile;

    //Get file location
    char *filepath = SDL_GetPrefPath("0x00101010", "SamsSearch");

    outFile.open(std::string(filepath) + "settings", std::ios::binary);

    if (outFile) {
        outFile.write((char *) &m_settings, sizeof(m_settings));
    } else {
        std::cout << "Error writing to file" << std::endl;
    }

    outFile.close();
    SDL_free(filepath);
}

void SettingsManager::resetSettings() {
    setTitleMusicEnabled(true);
    setGameMusicEnabled(true);
    setMusicVolume(50);
    setGameVolume(70);
}