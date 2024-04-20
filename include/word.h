#ifndef CS8_GUILIBRARY_WORD_H
#define CS8_GUILIBRARY_WORD_H

#include "font-manager.h"
#include "mouse-event.h"
#include "states.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class Word : public sf::Text, public State {
  public:
    Word();
    Word(FontEnum font);

    void update();
    void eventHandler(sf::RenderWindow &window, sf::Event event);

  private:
};

#endif // !CS8_GUILIBRARY_WORD_H
