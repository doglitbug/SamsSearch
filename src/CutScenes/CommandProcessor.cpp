#include "CommandProcessor.h"

void CommandProcessor::AddCommand(Command *command) {
    m_commands.push_back(command);
}

void CommandProcessor::ProcessCommands(const float deltaTime) {
    if (m_commands.empty()) {
        return;
    }

    if (m_commands.front()->completed) {
        delete m_commands.front();
        m_commands.pop_front();
        return;
    }

    if (!m_commands.front()->started) {
        m_commands.front()->start();
        m_commands.front()->started = true;
        return;
    }

    m_commands.front()->update(deltaTime);
}

bool CommandProcessor::showingDialog() const {
    if (m_commands.empty()) {
        return false;
    }

    if (const auto tp = dynamic_cast<cmdShowDialog *>(m_commands.front())) {
        if (tp->started && !tp->completed)
            return true;
    }
    return false;
}
