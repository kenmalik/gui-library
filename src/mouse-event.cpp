#include "mouse-event.h"

bool MouseEvent::isHovered(const sf::FloatRect &bounds,
                           const sf::RenderWindow &window) {
    return bounds.contains((sf::Vector2f)sf::Mouse::getPosition(window));
}

bool MouseEvent::isClicked(const sf::FloatRect &bounds,
                           const sf::RenderWindow &window) {
    return bounds.contains((sf::Vector2f)sf::Mouse::getPosition(window)) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
