#include "padding.h"

Padding::Padding(GuiComponent *component, float padding)
    : GUIComponentDecorator(component), paddingTop(padding),
      paddingBottom(padding), paddingLeft(padding), paddingRight(padding) {
    paddingBounds =
        sf::RectangleShape({padding * 2 + component->getGlobalBounds().width,
                            padding * 2 + component->getGlobalBounds().height});
    paddingBounds.setPosition(component->getGlobalBounds().left,
                              component->getGlobalBounds().top);
    paddingBounds.setFillColor(defaultFillColor);
    component->setPosition(component->getPosition().x + padding,
                           component->getPosition().y + padding);
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
