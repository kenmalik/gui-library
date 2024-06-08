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

    sf::Transform getParentTransfrom() const override;
    void setParentTransfrom(const sf::Transform &transform) override;

    void update() override;

  private:
    sf::Transform parentTransform = sf::Transform::Identity;

    float paddingTop;
    float paddingBottom;
    float paddingLeft;
    float paddingRight;

    sf::RectangleShape paddingBounds;

    std::function<sf::FloatRect()> hitboxBehavior =
        std::bind(&Padding::getGlobalBounds, this);

    sf::Color defaultFillColor = sf::Color::Transparent;

    sf::Transform getTotalTransform() const;
};

#endif // !CS8_GUILIBRARY_PADDING_H
