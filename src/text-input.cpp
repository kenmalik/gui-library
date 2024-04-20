#include "text-input.h"
#include <SFML/Graphics/RectangleShape.hpp>

TextInput::TextInput() : TextInput(UBUNTU_R, {90, 30}) {}

TextInput::TextInput(FontEnum font, sf::Vector2f size) {
    text.setFont(FontManager::getFont(font));
    background.setSize(size);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Green);
    background.setFillColor(sf::Color::Cyan);
}

void TextInput::setString(const std::string &string) { text.setString(string); }

void TextInput::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (MouseEvent::isHovered(background.getGlobalBounds(), window)) {
        this->enableState(HOVERED);
    } else {
        this->disableState(HOVERED);
    }

    if (MouseEvent::isClicked(background.getGlobalBounds(), window)) {
        this->enableState(CLICKED);
    } else {
        this->disableState(CLICKED);
    }
}

void TextInput::update() {
    if (this->getState(HOVERED)) {
        background.setFillColor(sf::Color::Blue);
    } else {
        background.setFillColor(sf::Color::Cyan);
    }

    if (this->getState(CLICKED)) {
        background.setFillColor(sf::Color::Red);
    }
}

void TextInput::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    window.draw(background);
    window.draw(text);
}

Snapshot &TextInput::getSnapshot() { return snapshot; }

void TextInput::applySnapshot(const Snapshot &snapshot) {}
