#ifndef CS8_GRAPHICSLIBRARY_STATES_H
#define CS8_GRAPHICSLIBRARY_STATES_H

#include "state-enum.h"
#include <map>

class State {
  public:
    State();

    bool getState(StateEnum state) const;
    void disableState(StateEnum state);
    void enableState(StateEnum state);
    void toggleState(StateEnum state);

  private:
    std::map<StateEnum, bool> states;
};

#endif // !CS8_GRAPHICSLIBRARY_STATES_H
