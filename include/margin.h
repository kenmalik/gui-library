#ifndef CS8_GUILIBRARY_MARGIN_H
#define CS8_GUILIBRARY_MARGIN_H

#include "gui-component-decorator.h"
#include "gui-component.h"
#include <SFML/Graphics/Rect.hpp>

class Margin : public GUIComponentDecorator {
  public:
    Margin(GuiComponent *component, float margin);
    Margin(GuiComponent *component, float marginTopBottom,
           float marginLeftRight);
    Margin(GuiComponent *component, float marginTop, float marginLeftRight,
           float marginBottom);
    Margin(GuiComponent *component, float marginTop, float marginRight,
           float marginBottom, float marginLeft);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    sf::FloatRect getGlobalBounds() const override;

    sf::FloatRect getHitbox() const override;
    void setHitboxBehavior(std::function<sf::FloatRect()>) override;

  private:
    float marginTop;
    float marginBottom;
    float marginLeft;
    float marginRight;

    GuiComponent *component;
    sf::FloatRect marginBounds;
};

#endif // !CS8_GUILIBRARY_MARGIN_H
