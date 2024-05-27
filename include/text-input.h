#ifndef CS8_GUILIBRARY_TEXTINPUT_H
#define CS8_GUILIBRARY_TEXTINPUT_H

#include "font-enum.h"
#include "gui-component.h"
#include "snapshot.h"
#include "states.h"
#include "submittable.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstddef>
#include <functional>
#include <string>

class TextInput : public State, public GuiComponent, public Submitable {
  public:
    TextInput();
    TextInput(FontEnum font, sf::Vector2f size = {360, 30});

    const sf::String &getString() const;
    void setString(const std::string &string);

    const sf::String &getLabel() const;
    void setLabel(const std::string &string);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;

    Snapshot &getSnapshot() override;
    void applySnapshot(const Snapshot &snapshot) override;

    void setBackgroundColor(const sf::Color &color);
    void setPosition(sf::Vector2f position);
    void setSubmitBehavior(std::function<void()> submitBehavior);

    sf::FloatRect getGlobalBounds() const override;

  private:
    static constexpr unsigned int BACKSPACE = 8;
    static constexpr unsigned int DEL = 127;
    static constexpr unsigned int SPACE = 32;
    static constexpr unsigned int TILDA = 126;

    static constexpr unsigned int CURSOR_BLINK_ON = 450;
    static constexpr unsigned int CURSOR_BLINK_OFF = 450;
    sf::Clock cursorTimer;
    bool isCursorVisible;

    size_t cursorIndex;
    sf::RectangleShape cursor;

    sf::Text label;
    sf::Text text;
    sf::RectangleShape background;

    Snapshot snapshot;

    void handleTextInput(unsigned int unicode);
    void moveCursor();
    void moveTextBox();

    void submit() override;
    std::function<void()> submitBehavior;
};

#endif // !CS8_GUILIBRARY_TEXTINPUT_H
