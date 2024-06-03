#include "padding.h"
#include "gui-component-decorator.h"

Padding::Padding(GuiComponent *component, float padding)
    : Padding(component, padding, padding, padding, padding) {}

Padding::Padding(GuiComponent *component, float paddingTopBottom,
                 float paddingLeftRight)
    : Padding(component, paddingTopBottom, paddingLeftRight, paddingTopBottom,
              paddingLeftRight) {}

Padding::Padding(GuiComponent *component, float paddingTop,
                 float paddingLeftRight, float paddingBottom)
    : Padding(component, paddingTop, paddingLeftRight, paddingBottom,
              paddingLeftRight) {}

Padding::Padding(GuiComponent *component, float paddingTop, float paddingRight,
                 float paddingBottom, float paddingLeft)
    : GUIComponentDecorator(component), paddingTop(paddingTop),
      paddingBottom(paddingBottom), paddingLeft(paddingLeft),
      paddingRight(paddingRight) {
    paddingBounds = sf::RectangleShape(
        {paddingLeft + paddingRight + component->getGlobalBounds().width,
         paddingTop + paddingBottom + component->getGlobalBounds().height});
    paddingBounds.setPosition(component->getGlobalBounds().left,
                              component->getGlobalBounds().top);
    paddingBounds.setFillColor(defaultFillColor);
    component->setPosition(component->getPosition().x + paddingLeft,
                           component->getPosition().y + paddingTop);
}

void Padding::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(paddingBounds, states);
    GUIComponentDecorator::draw(window, states);
}

sf::FloatRect Padding::getGlobalBounds() const {
    return getTransform().transformRect(paddingBounds.getGlobalBounds());
}

void Padding::setBackgroundColor(const sf::Color &color) {
    paddingBounds.setFillColor(color);
}
