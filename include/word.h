#ifndef CS8_GUILIBRARY_WORD_H
#define CS8_GUILIBRARY_WORD_H

#include "font-enum.h"
#include "gui-component.h"
#include "states.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

class Word : public GuiComponent, public State {
  public:
    Word();
    Word(FontEnum font);

    void setText(std::string text);

    void update() override;
    void eventHandler(sf::RenderWindow &window, sf::Event event) override;

    void setFont(FontEnum font);
    void setCharacterSize(unsigned int size);

    void setIsHoverable(bool hoverable);
    bool getIsHoverable() const;

    void setIsUnderlined(bool isUnderlined);

    virtual void draw(sf::RenderTarget &window,
                      sf::RenderStates states) const override;

    virtual sf::FloatRect getGlobalBounds() const override;

    void setTextColor(const sf::Color &color);
    void setBackgroundColor(const sf::Color &color);

    sf::FloatRect getHitbox() const override;
    void setHitboxBehavior(std::function<sf::FloatRect()>) override;

  private:
    sf::Text text;

    sf::Color defaultTextColor = sf::Color::Black;
    sf::Color hoverTextColor = sf::Color::Blue;
    sf::Color clickTextColor = sf::Color::Red;

    bool isHoverable = false;

    void adjustTextPosition();

    std::function<sf::FloatRect()> hitboxBehavior =
        std::bind(&Word::getGlobalBounds, this);
};

#endif // !CS8_GUILIBRARY_WORD_H
