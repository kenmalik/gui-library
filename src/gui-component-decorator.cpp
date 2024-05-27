#include "gui-component-decorator.h"

GUIComponentDecorator::GUIComponentDecorator(GuiComponent *component)
    : component(component){};

void GUIComponentDecorator::draw(sf::RenderTarget &window,
                                 sf::RenderStates states) const {
    component->draw(window, states);
}

void GUIComponentDecorator::eventHandler(sf::RenderWindow &window,
                                         sf::Event event) {
    component->eventHandler(window, event);
}

void GUIComponentDecorator::update() { component->update(); }

Snapshot &GUIComponentDecorator::getSnapshot() {
    return component->getSnapshot();
}

void GUIComponentDecorator::applySnapshot(const Snapshot &snapshot) {
    component->applySnapshot(snapshot);
}
