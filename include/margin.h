#ifndef CS8_GUILIBRARY_MARGIN_H
#define CS8_GUILIBRARY_MARGIN_H

#include "gui-component-decorator.h"
#include "gui-component.h"
#include <SFML/Graphics/Rect.hpp>

class Margin : public GUIComponentDecorator {
  public:
    Margin(GuiComponent *component, float margin);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    float marginTop;
    float marginBottom;
    float marginLeft;
    float marginRight;

    sf::FloatRect getGlobalBounds() const;

  private:
    GuiComponent *component;
    sf::FloatRect marginBounds;
};

#endif // !CS8_GUILIBRARY_MARGIN_H
