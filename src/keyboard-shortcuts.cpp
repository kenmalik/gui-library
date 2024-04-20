#include "keyboard-shortcuts.h"
#include <SFML/Window/Keyboard.hpp>

bool KeyboardShortcuts::isUndo() {
    return (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) &&
           sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
}
