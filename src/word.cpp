#include "word.h"
#include "font-manager.h"
#include "mouse-event.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>

Word::Word() : Word(UBUNTU_R) {}

Word::Word(FontEnum font) {
    text.setFont(FontManager::getFont(font));
    text.setFillColor(defaultTextColor);
}

void Word::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (MouseEvent::isHovered(getGlobalBounds(), window)) {
        this->enableState(HOVERED);
    } else {
        this->disableState(HOVERED);
    }

    if (MouseEvent::isClicked(getGlobalBounds(), window)) {
        this->enableState(CLICKED);
    } else {
        this->disableState(CLICKED);
    }
}

void Word::update() {
    if (isHoverable && this->getState(HOVERED)) {
        text.setFillColor(hoverTextColor);
        setIsUnderlined(true);
    } else {
        text.setFillColor(defaultTextColor);
        setIsUnderlined(false);
    }

    if (this->getState(CLICKED)) {
        text.setFillColor(clickTextColor);
    }
}

void Word::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(text, states);
}

sf::FloatRect Word::getGlobalBounds() const {
    return getTotalTransform().transformRect(text.getGlobalBounds());
}

void Word::setText(std::string text) {
    this->text.setString(text);
    adjustTextPosition();
}

void Word::setIsHoverable(bool hoverable) { this->isHoverable = hoverable; }

bool Word::getIsHoverable() const { return isHoverable; }

void Word::setFont(FontEnum font) {
    text.setFont(FontManager::getFont(font));
    adjustTextPosition();
}

void Word::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
    adjustTextPosition();
}

void Word::setIsUnderlined(bool isUnderlined) {
    if (isUnderlined) {
        text.setStyle(sf::Text::Underlined);
    } else {
        text.setStyle(sf::Text::Regular);
    }
}

void Word::adjustTextPosition() {
    text.setPosition(getPosition());
    text.move(text.getPosition().x - text.getGlobalBounds().left,
              text.getPosition().y - text.getGlobalBounds().top);
}

void Word::setTextColor(const sf::Color &color) {
    text.setFillColor(color);
    defaultTextColor = color;
}

sf::FloatRect Word::getHitbox() const { return hitboxBehavior(); }

void Word::setHitboxBehavior(std::function<sf::FloatRect()> hitboxBehavior) {
    this->hitboxBehavior = hitboxBehavior;
}

sf::Transform Word::getParentTransfrom() const { return parentTransform; }

void Word::setParentTransfrom(const sf::Transform &transform) {
    parentTransform = transform;
}

sf::Transform Word::getTotalTransform() const {
    return getTransform() * parentTransform;
}
