#ifndef CS8_GUILIBRARY_MOUSEEVENT_H
#define CS8_GUILIBRARY_MOUSEEVENT_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class MouseEvent {
  public:
    static bool isHovered(const sf::FloatRect &bounds,
                          const sf::RenderWindow &window);
    static bool isClicked(const sf::FloatRect &bounds,
                          const sf::RenderWindow &window);
};

#endif // !CS8_GUILIBRARY_MOUSEEVENT_H
