#include "states.h"

State::State() {
    for (int i = 0; i < LAST_STATE; i++) {
        states[static_cast<StateEnum>(i)] = false;
    }
}

bool State::getState(StateEnum state) const { return states.at(state); }

void State::disableState(StateEnum state) { states[state] = false; }

void State::enableState(StateEnum state) { states[state] = true; }

void State::toggleState(StateEnum state) { states[state] = !states[state]; }
