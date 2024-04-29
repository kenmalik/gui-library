#ifndef CS8_GUILIBRARY_HISTORY_H
#define CS8_GUILIBRARY_HISTORY_H

#include "history-node.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <stack>

class History {
  public:
    static void pushHistory(const HistoryNode &snapshot);
    static HistoryNode &top();
    static void pop();
    static void eventHandler(sf::RenderWindow &window, sf::Event event);

  private:
    static std::stack<HistoryNode> stack;
};

#endif // !CS8_GUILIBRARY_HISTORY_H
