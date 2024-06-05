#include "composite-gui-component.h"
#include "gui-component.h"
#include <SFML/Graphics/Rect.hpp>
#include <algorithm>
#include <iostream>

CompositeGUIComponent::CompositeGUIComponent() {}

void CompositeGUIComponent::draw(sf::RenderTarget &window,
                                 sf::RenderStates states) const {
    states.transform *= getTransform();
    for (auto &child : children) {
        child->draw(window, states);
    }
}

void CompositeGUIComponent::eventHandler(sf::RenderWindow &window,
                                         sf::Event event) {
    for (auto &child : children) {
        child->eventHandler(window, event);
    }
}

void CompositeGUIComponent::update() {
    for (auto &child : children) {
        child->update();
    }
}

void CompositeGUIComponent::addChild(GuiComponent *component) {
    children.push_back(component);
}

sf::FloatRect CompositeGUIComponent::getHitbox() const {
    return hitboxBehavior();
}

sf::FloatRect CompositeGUIComponent::getGlobalBounds() const {
    if (!children.empty()) {
        auto leftChild = std::max_element(children.begin(), children.end(),
                                          [](GuiComponent *a, GuiComponent *b) {
                                              return a->getGlobalBounds().left <
                                                     b->getGlobalBounds().left;
                                          });
        auto rightChild = std::max_element(
            children.begin(), children.end(),
            [](GuiComponent *a, GuiComponent *b) {
                return a->getGlobalBounds().left + a->getGlobalBounds().width <
                       b->getGlobalBounds().left + b->getGlobalBounds().width;
            });
        auto topChild = std::min_element(children.begin(), children.end(),
                                         [](GuiComponent *a, GuiComponent *b) {
                                             return a->getGlobalBounds().top <
                                                    b->getGlobalBounds().top;
                                         });
        auto bottomChild = std::max_element(
            children.begin(), children.end(),
            [](GuiComponent *a, GuiComponent *b) {
                return a->getGlobalBounds().top + a->getGlobalBounds().height <
                       b->getGlobalBounds().top + b->getGlobalBounds().height;
            });
        float left = (*leftChild)->getGlobalBounds().left;
        float right = (*rightChild)->getGlobalBounds().left +
                      (*rightChild)->getGlobalBounds().width;
        float top = (*topChild)->getGlobalBounds().top;
        float bottom = (*bottomChild)->getGlobalBounds().top +
                       (*bottomChild)->getGlobalBounds().height;
        return {left, top, right - left, bottom - top};

    } else {
        std::cerr << "Composite empty" << std::endl;
        exit(1);
    }
}

void CompositeGUIComponent::setHitboxBehavior(
    std::function<sf::FloatRect()> hitboxBehavior) {
    this->hitboxBehavior = hitboxBehavior;
}
