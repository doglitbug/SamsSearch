#pragma once
#include <variant>
#include <string>
#include <vector>
#include "../Observers.h"

// Any change to this struct will probably require deleting the settings already on disk!
struct settings
{
    bool titleMusicEnabled;
    int titleMusicVolume;
    bool gameMusicEnabled;
    int gameMusicVolume;
    int gameVolume;
    bool fullScreen;
};

class Settings : public ISubject
{
public:
    Settings();
    ~Settings() = default;

    // Observers
    void addObserver(IObserver *observer);
    void removeObserver(IObserver *observer);
    void notifyObservers(const std::string &message, MyType newValue);

    void load();
    void save();
    void reset();

    // Audio
    bool getTitleMusicEnabled() const;
    void setTitleMusicEnabled(bool enabled);
    int getTitleMusicVolume() const;
    void setTitleMusicVolume(int volume);

    bool getGameMusicEnabled() const;
    void setGameMusicEnabled(bool enabled);
    int getGameMusicVolume() const;
    void setGameMusicVolume(int volume);

    int getGameVolume() const;
    void setGameVolume(int volume);

    // Video
    bool getFullScreen() const;
    void setFullScreen(bool enabled);

private:
    settings m_settings{};
    std::vector<IObserver *> observers;
};
