#pragma once

#include <variant>
#include <string>
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