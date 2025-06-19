#pragma once

#include <list>
#include "Commands.h"

class CommandProcessor {
public:
    CommandProcessor(){};
    ~CommandProcessor(){}


    void AddCommand(Command *command);
    void ProcessCommands(float deltaTime);
    bool UserControl() const {return m_commands.empty();}
    bool showingDialog() const;

    private:
    std::list<Command*> m_commands;
};