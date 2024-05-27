#ifndef CS8_GUILIBRARY_BOUNDED_H
#define CS8_GUILIBRARY_BOUNDED_H

#include <SFML/Graphics/Rect.hpp>

class Bounded {
  public:
    virtual sf::FloatRect getGlobalBounds() const = 0;
};

#endif // !CS8_GUILIBRARY_BOUNDED_H
