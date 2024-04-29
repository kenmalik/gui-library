#include "history.h"
#include "history-node.h"
#include "keyboard-shortcuts.h"
#include <stack>

std::stack<HistoryNode> History::stack;

void History::pushHistory(const HistoryNode &snapshot) { stack.push(snapshot); }

HistoryNode &History::top() { return stack.top(); }

void History::pop() { stack.pop(); }

void History::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (stack.size() > 1 && KeyboardShortcuts::isUndo()) {
        stack.pop();
        stack.top().component->applySnapshot(stack.top().snapshot);
    }
}
