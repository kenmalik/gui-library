#include "margin.h"
#include "gui-component-decorator.h"
#include <SFML/Graphics/Rect.hpp>

Margin::Margin(GuiComponent *component, float margin)
    : GUIComponentDecorator(component), marginTop(margin), marginBottom(margin),
      marginLeft(margin), marginRight(margin) {
    marginBounds = sf::FloatRect(
        component->getGlobalBounds().left, component->getGlobalBounds().top,
        margin * 2 + component->getGlobalBounds().width,
        margin * 2 + component->getGlobalBounds().height);
    component->setPosition(component->getPosition().x + margin,
                           component->getPosition().y + margin);
}

void Margin::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    GUIComponentDecorator::draw(window, states);
}

sf::FloatRect Margin::getGlobalBounds() const {
    return getTransform().transformRect(marginBounds);
}
