#ifndef CS8_GUILIBRARY_WORD_H
#define CS8_GUILIBRARY_WORD_H

#include "font-enum.h"
#include "gui-component.h"
#include "states.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

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

    virtual Snapshot &getSnapshot() override;
    virtual void applySnapshot(const Snapshot &snapshot) override;
    virtual sf::FloatRect getGlobalBounds() const override;

    void setPadding(float padding);
    void setPadding(float paddingTopBottom, float paddingLeftRight);
    void setPadding(float paddingTop, float paddingLeftRight,
                    float paddingBottom);
    void setPadding(float paddingTop, float paddingRight, float paddingBottom,
                    float paddingLeft);

    void setTextColor(const sf::Color &color);
    void setBackgroundColor(const sf::Color &color);

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);

  private:
    sf::Text text;
    sf::RectangleShape background;

    sf::Color defaultTextColor = sf::Color::Black;
    sf::Color hoverTextColor = sf::Color::Blue;
    sf::Color clickTextColor = sf::Color::Red;

    sf::Color defaultBackgroundColor = sf::Color::Transparent;
    sf::Color hoverBackgroundColor = sf::Color::White;

    float paddingTop = 0;
    float paddingBottom = 0;
    float paddingLeft = 0;
    float paddingRight = 0;

    bool isHoverable = false;

    void resizeBackground();
    void adjustTextPosition();

    Snapshot snapshot;
};

#endif // !CS8_GUILIBRARY_WORD_H
