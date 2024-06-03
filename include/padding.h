#ifndef CS8_GUILIBRARY_PADDING_H
#define CS8_GUILIBRARY_PADDING_H

#include "gui-component-decorator.h"
#include "gui-component.h"
#include <SFML/Graphics/RectangleShape.hpp>

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

  private:
    float paddingTop;
    float paddingBottom;
    float paddingLeft;
    float paddingRight;

    GuiComponent *component;
    sf::RectangleShape paddingBounds;

    sf::Color defaultFillColor = sf::Color::Transparent;
};

#endif // !CS8_GUILIBRARY_PADDING_H
