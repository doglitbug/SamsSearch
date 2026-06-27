#pragma once
#include <variant>
#include <string>
#include <vector>

// Any change to this struct will probably require deleting the settings already on disk!
struct settings
{
    bool titleMusicEnabled;
    bool gameMusicEnabled;
    int musicVolume;
    int gameVolume;
    bool fullScreen;
};

using MyType = std::variant<int, float, bool>;
class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void onNotify(const std::string &message, MyType newValue) = 0;
};

class ISubject
{
public:
    virtual ~ISubject() = default;
    virtual void addObserver(IObserver *observer) = 0;
    virtual void removeObserver(IObserver *observer) = 0;
    virtual void notifyObservers(const std::string &message, MyType newValue) = 0;
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

    bool getGameMusicEnabled() const;
    void setGameMusicEnabled(bool enabled);

    int getMusicVolume() const;
    void setMusicVolume(int volume);

    int getGameVolume() const;
    void setGameVolume(int volume);

    // Video
    bool getFullScreen() const;
    void setFullScreen(bool enabled);


    std::vector<IObserver *> observers;
    
private:
    settings m_settings{};
    
};
