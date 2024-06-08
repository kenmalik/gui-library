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

    sf::Transform getParentTransfrom() const override;
    void setParentTransfrom(const sf::Transform &transform) override;

    void update() override;

  private:
    sf::Transform parentTransform = sf::Transform::Identity;

    float marginTop;
    float marginBottom;
    float marginLeft;
    float marginRight;

    sf::FloatRect marginBounds;

    sf::Transform getTotalTransform() const;
};

#endif // !CS8_GUILIBRARY_MARGIN_H
