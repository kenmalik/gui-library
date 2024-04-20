#ifndef CS8_GUILIBRARY_EVENTHANDLER_H
#define CS8_GUILIBRARY_EVENTHANDLER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class EventHandler {
  public:
    virtual void eventHandler(sf::RenderWindow &window, sf::Event event) = 0;
    virtual void update() = 0;
};

#endif // CS8_GUILIBRARY_EVENTHANDLER_H
