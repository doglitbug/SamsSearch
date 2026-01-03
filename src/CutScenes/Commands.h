#pragma once
#include <string>
#include <vector>
#include "../../Managers/AssetManager.h"
#include "GameObjects/GameObject.h"
#include "Vector2D.h"

class Command {
public:
    Command() {}
    virtual ~Command() {}

    virtual void start() {};
    virtual void update(float deltaTime) {};
    //virtual void onExit();

    bool started = false;
    bool completed = false;
};

///
class cmdShowDialog final : public Command {
public:
    /// @brief Display some dialog
    /// @param dialogFace Sprite to display as the face
    /// @param dialogLines Dialog lines
    cmdShowDialog(const Sprite &dialogFace, const std::vector<std::string> &dialogLines);
    ~cmdShowDialog() override {};

    void start() override;
    void update(float deltaTime) override;

private:
    Sprite sprite;
    std::vector<std::string> dialog;
};

class cmdMoveTo final : public Command {
public:
    /// @brief Move a GameObjectCreature to destination
    /// @param gameObjectCreature GameObjectCreature to move
    /// @param x Destination x
    /// @param y Destination y
    /// @param duration Time to take: 0 is instant, -1 will default to normal objects speed
    cmdMoveTo(GameObject *gameObjectCreature, const float x, const float y, float duration = 0.0f);
    ~cmdMoveTo() override {};

    void start() override;
    void update(float deltaTime) override;

private:
    GameObject *m_gameObject;
    Vector2D m_startPosition;
    Vector2D m_endPosition;
    float m_duration;
    float m_timeSoFar;
};

class cmdWait final :public Command {
    public:
    /// Wait for a specified amount of time (in seconds)
    /// @param duration Amount of time to wait
    explicit cmdWait(float duration);
    ~cmdWait() override {};

    void update(float deltaTime) override;

    private:
    float m_duration;
    float m_timeSoFar;
};

