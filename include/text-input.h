#ifndef CS8_GUILIBRARY_TEXTINPUT_H
#define CS8_GUILIBRARY_TEXTINPUT_H

#include "font-manager.h"
#include "gui-component.h"
#include "mouse-event.h"
#include "snapshot.h"
#include "states.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

class TextInput : public State, public GuiComponent {
  public:
    TextInput();
    TextInput(FontEnum font, sf::Vector2f size = {90, 30});

    void setString(const std::string &string);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;

    Snapshot &getSnapshot() override;
    void applySnapshot(const Snapshot &snapshot) override;

  private:
    sf::Text label;
    sf::Text text;
    sf::RectangleShape background;
    Snapshot snapshot;
};

#endif // !CS8_GUILIBRARY_TEXTINPUT_H
