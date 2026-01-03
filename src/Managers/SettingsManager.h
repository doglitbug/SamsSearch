#pragma once

#include "SDL3/SDL.h"
#include "AssetManager.h"

//Any chance to this struct will probably require deleting the settings already on disk!
struct settings {
    bool titleMusicEnabled;
    bool gameMusicEnabled;
    int musicVolume;
    int gameVolume;
};

class SettingsManager {
public:
    static SettingsManager *get() {
        static SettingsManager me;
        return &me;
    };

    // Singleton
    SettingsManager(SettingsManager &other) = delete;

    void operator=(const SettingsManager &) = delete;

    // region Settings
    void loadSettings();

    void saveSettings();

    void resetSettings();
    // endregion

    // region Music
    static bool getTitleMusicEnabled() { return get()->m_settings.titleMusicEnabled; }

    void setTitleMusicEnabled(bool enabled) {
        m_settings.titleMusicEnabled = enabled;
        if (!enabled) AssetManager::get()->stopTitleMusic();
    }

    static bool getGameMusicEnabled() { return get()->m_settings.gameMusicEnabled; };

    void setGameMusicEnabled(const bool enabled) { m_settings.gameMusicEnabled = enabled; }

    static int getMusicVolume() { return get()->m_settings.musicVolume; };

    void setMusicVolume(const int volume) {
        m_settings.musicVolume = volume;
        AssetManager::get()->setMusicVolume(volume);
    };

    static int getGameVolume() { return get()->m_settings.gameVolume; };

    void setGameVolume(const int volume) {
        m_settings.gameVolume = volume;
        AssetManager::get()->setGameVolume(volume);
    };

    // endregion

private:
    SettingsManager() {};

    ~SettingsManager() = default;

    settings m_settings;
};