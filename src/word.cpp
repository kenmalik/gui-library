#include "word.h"

Word::Word() : Word(UBUNTU_R) {}

Word::Word(FontEnum font) : sf::Text() { setFont(FontManager::getFont(font)); }

void Word::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (MouseEvent::isHovered(this->getGlobalBounds(), window)) {
        this->enableState(HOVERED);
    } else {
        this->disableState(HOVERED);
    }

    if (MouseEvent::isClicked(this->getGlobalBounds(), window)) {
        this->enableState(CLICKED);
    } else {
        this->disableState(CLICKED);
    }
}

void Word::update() {
    if (this->getState(HOVERED)) {
        this->setFillColor(sf::Color::Blue);
    } else {
        this->setFillColor(sf::Color::White);
    }

    if (this->getState(CLICKED)) {
        this->setFillColor(sf::Color::Red);
    }
}
