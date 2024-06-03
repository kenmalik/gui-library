#include "word.h"
#include "font-manager.h"
#include "mouse-event.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>

Word::Word() : Word(UBUNTU_R) {}

Word::Word(FontEnum font) {
    text.setFont(FontManager::getFont(font));
    text.setFillColor(defaultTextColor);
    background.setFillColor(defaultBackgroundColor);
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
    window.draw(background, states);
    window.draw(text, states);
}

Snapshot &Word::getSnapshot() { return snapshot; }

void Word::applySnapshot(const Snapshot &snapshot) {
    text.setString(snapshot.getData());
    adjustTextPosition();
    resizeBackground();
}

sf::FloatRect Word::getGlobalBounds() const {
    return getTransform().transformRect(background.getGlobalBounds());
}

void Word::setText(std::string text) {
    this->text.setString(text);
    adjustTextPosition();
    resizeBackground();
}

void Word::resizeBackground() {
    background.setPosition(getPosition());
    text.move(paddingLeft, paddingTop);
    background.setSize(
        {text.getGlobalBounds().width + paddingLeft + paddingRight,
         text.getGlobalBounds().height + paddingTop + paddingBottom});
}

void Word::setIsHoverable(bool hoverable) { this->isHoverable = hoverable; }

bool Word::getIsHoverable() const { return isHoverable; }

void Word::setFont(FontEnum font) {
    text.setFont(FontManager::getFont(font));
    adjustTextPosition();
    resizeBackground();
}

void Word::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
    adjustTextPosition();
    resizeBackground();
}

void Word::setPadding(float padding) {
    paddingTop = padding;
    paddingBottom = padding;
    paddingLeft = padding;
    paddingRight = padding;
    resizeBackground();
}

void Word::setPadding(float paddingTopBottom, float paddingLeftRight) {
    paddingTop = paddingTopBottom;
    paddingBottom = paddingTopBottom;
    paddingLeft = paddingLeftRight;
    paddingRight = paddingLeftRight;
    resizeBackground();
}

void Word::setPadding(float paddingTop, float paddingLeftRight,
                      float paddingBottom) {
    this->paddingTop = paddingTop;
    this->paddingBottom = paddingBottom;
    paddingLeft = paddingLeftRight;
    paddingRight = paddingLeftRight;
    resizeBackground();
}

void Word::setPadding(float paddingTop, float paddingRight, float paddingBottom,
                      float paddingLeft) {
    this->paddingTop = paddingTop;
    this->paddingBottom = paddingBottom;
    this->paddingLeft = paddingLeft;
    this->paddingRight = paddingRight;
    resizeBackground();
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

void Word::setBackgroundColor(const sf::Color &color) {
    background.setFillColor(color);
    defaultBackgroundColor = color;
}
