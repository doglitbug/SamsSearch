#include "StateMachine.h"

void StateMachine::update(float deltaTime) {
    m_gameStateStack.back()->update(deltaTime);
    if (m_requestedChangeType != NOCHANGE) {
        changeState();
    }
}

void StateMachine::render() const
{
    m_gameStateStack.back()->render();
}

void StateMachine::registerState(const std::string& stateID, BaseState *pState) {
    //Is this the first state, if so, set as default
    if (m_gameStateStack.empty())
    {
        m_gameStateStack.push_back(pState);
    }
    m_gameStates[stateID] = pState;
}

void StateMachine::setInitialState(const std::string& stateID) {
    if (m_gameStates[stateID]) {
        m_gameStateStack.push_back(m_gameStates[stateID]);
        m_gameStateStack.back()->onEnter();
    } else {
        std::cout << "Initial state " << stateID << " not found" << std::endl;
    }
}

void StateMachine::changeState(const std::string& stateID) {
    if (m_gameStates[stateID]) {
        m_requestedState = stateID;
        m_requestedChangeType = CHANGE;
    } else {
        std::cout << "State "<< stateID << " not found" << std::endl;
    }
}

void StateMachine::pushState(const std::string& stateID) {
    if(m_gameStates[stateID]) {
        m_requestedState = stateID;
        m_requestedChangeType = PUSH;
    } else {
        std::cout << "State "<< stateID << " not found" << std::endl;
    }
}

void StateMachine::popState() {
    m_requestedChangeType = POP;
}

void StateMachine::changeState() {
    switch (m_requestedChangeType) {
        case CHANGE:
            //Remove current states
            for (BaseState *gs: m_gameStateStack) {
                gs->onExit();
            }
            m_gameStateStack.clear();

            //Add new one
            m_gameStateStack.push_back(m_gameStates[m_requestedState]);
            m_gameStateStack.back()->onEnter();
            break;
        case PUSH:
            m_gameStateStack.push_back(m_gameStates[m_requestedState]);
            m_gameStateStack.back()->onEnter();
            break;
        case POP:
            m_gameStateStack.back()->onExit();
            m_gameStateStack.pop_back();
            break;
        case NOCHANGE:
            break;
    }
    m_requestedChangeType = NOCHANGE;
}