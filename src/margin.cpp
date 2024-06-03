#include "margin.h"
#include "gui-component-decorator.h"
#include <SFML/Graphics/Rect.hpp>

Margin::Margin(GuiComponent *component, float margin)
    : Margin(component, margin, margin, margin, margin) {}

Margin::Margin(GuiComponent *component, float marginTopBottom,
               float marginLeftRight)
    : Margin(component, marginTopBottom, marginLeftRight, marginTopBottom,
             marginLeftRight) {}

Margin::Margin(GuiComponent *component, float marginTop, float marginLeftRight,
               float marginBottom)
    : Margin(component, marginTop, marginLeftRight, marginBottom,
             marginLeftRight) {}

Margin::Margin(GuiComponent *component, float marginTop, float marginRight,
               float marginBottom, float marginLeft)
    : GUIComponentDecorator(component), marginTop(marginTop),
      marginBottom(marginBottom), marginLeft(marginLeft),
      marginRight(marginRight) {
    marginBounds = sf::FloatRect(
        component->getGlobalBounds().left, component->getGlobalBounds().top,
        marginLeft + marginRight + component->getGlobalBounds().width,
        marginTop + marginBottom + component->getGlobalBounds().height);
    component->setPosition(component->getPosition().x + marginLeft,
                           component->getPosition().y + marginTop);
}

void Margin::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    GUIComponentDecorator::draw(window, states);
}

sf::FloatRect Margin::getGlobalBounds() const {
    return getTransform().transformRect(marginBounds);
}
