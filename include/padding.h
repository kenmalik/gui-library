#ifndef CS8_GUILIBRARY_PADDING_H
#define CS8_GUILIBRARY_PADDING_H

#include "gui-component-decorator.h"
#include "gui-component.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

class Padding : public GUIComponentDecorator {
  public:
    Padding(GuiComponent *component, float padding);
    Padding(GuiComponent *component, float paddingTopBottom,
            float paddingLeftRight);
    Padding(GuiComponent *component, float paddingTop, float paddingLeftRight,
            float paddingBottom);
    Padding(GuiComponent *component, float paddingTop, float paddingRight,
            float paddingBottom, float paddingLeft);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
    void setBackgroundColor(const sf::Color &color);

    sf::FloatRect getGlobalBounds() const override;

    void setHitboxBehavior(std::function<sf::FloatRect()>) override;
    sf::FloatRect getHitbox() const override;

  private:
    float paddingTop;
    float paddingBottom;
    float paddingLeft;
    float paddingRight;

    GuiComponent *component;
    sf::RectangleShape paddingBounds;

    std::function<sf::FloatRect()> hitboxBehavior =
        std::bind(&Padding::getGlobalBounds, this);

    sf::Color defaultFillColor = sf::Color::Transparent;
};

#endif // !CS8_GUILIBRARY_PADDING_H
