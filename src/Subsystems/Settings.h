#pragma once

//Any change to this struct will probably require deleting the settings already on disk!
struct settings
{
    bool titleMusicEnabled;
    bool gameMusicEnabled;
    int musicVolume;
    int gameVolume;
    bool fullScreen;
};

class Settings
{
public:
    Settings();
    ~Settings() = default;

    void load();
    void save();
    void reset();

    // Audio
    bool getTitleMusicEnabled() const;
    void setTitleMusicEnabled(bool enabled);

    bool getGameMusicEnabled() const;
    void setGameMusicEnabled(bool enabled);

    int getMusicVolume() const;
    void setMusicVolume(int volume);

    int getGameVolume() const;
    void setGameVolume(int volume);

    // Video
    bool getFullScreen() const;
    void setFullScreen(bool enabled);

private:
    settings m_settings{};
};
