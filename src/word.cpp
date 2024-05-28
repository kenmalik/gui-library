#include "word.h"
#include "font-manager.h"
#include "mouse-event.h"
#include <SFML/Graphics/Text.hpp>
#include <iostream>

Word::Word() : Word(UBUNTU_R) {}

Word::Word(FontEnum font) {
    text.setFont(FontManager::getFont(font));
    text.setFillColor(defaultTextColor);
}

void Word::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (MouseEvent::isHovered(
            getTransform().transformRect(text.getGlobalBounds()), window)) {
        this->enableState(HOVERED);
    } else {
        this->disableState(HOVERED);
    }

    if (MouseEvent::isClicked(
            getTransform().transformRect(text.getGlobalBounds()), window)) {
        this->enableState(CLICKED);
    } else {
        this->disableState(CLICKED);
    }
}

void Word::update() {
    if (isHoverable && this->getState(HOVERED)) {
        text.setFillColor(sf::Color::Blue);
        setIsUnderlined(true);
    } else {
        text.setFillColor(defaultTextColor);
        setIsUnderlined(false);
    }

    if (this->getState(CLICKED)) {
        text.setFillColor(sf::Color::Red);
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
    background.setPosition(text.getGlobalBounds().left,
                           text.getGlobalBounds().top);
    text.setPosition(text.getPosition().x + paddingLeft,
                     text.getPosition().y + paddingTop);
    background.setSize(
        {text.getGlobalBounds().width + paddingLeft + paddingRight,
         text.getGlobalBounds().height + paddingTop + paddingBottom});
    std::cout << "Text: " << text.getGlobalBounds().width << std::endl;
    std::cout << "Bg: " << background.getGlobalBounds().width << std::endl;
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

void Word::addPadding(float padding) {
    paddingTop = padding;
    paddingBottom = padding;
    paddingLeft = padding;
    paddingRight = padding;
    adjustTextPosition();
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
    std::cout << text.getGlobalBounds().left - text.getPosition().x
              << std::endl;
    text.move(text.getPosition().x - text.getGlobalBounds().left,
              text.getPosition().y - text.getGlobalBounds().top);
}
