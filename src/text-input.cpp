#include "text-input.h"
#include "keyboard-shortcuts.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

TextInput::TextInput() : TextInput(UBUNTU_R, {90, 30}) {}

TextInput::TextInput(FontEnum font, sf::Vector2f size) {
    cursorIndex = 0;
    text.setFont(FontManager::getFont(font));
    background.setSize(size);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Green);
    background.setFillColor(sf::Color::Cyan);
}

void TextInput::setString(const std::string &string) {
    text.setString(string);
    cursorIndex = text.getString().getSize();
}

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

    if (event.type == sf::Event::TextEntered) {
        handleTextInput(event.text.unicode);
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left && cursorIndex > 0) {
            cursorIndex--;
        }
        if (event.key.code == sf::Keyboard::Right &&
            cursorIndex < text.getString().getSize()) {
            cursorIndex++;
        }
    }

    if (KeyboardShortcuts::isUndo()) {
        text.setString("Undo");
    }
}

void TextInput::handleTextInput(unsigned int unicode) {
    if (unicode == BACKSPACE && cursorIndex > 0) {
        text.setString(text.getString().substring(0, cursorIndex - 1) +
                       text.getString().substring(
                           cursorIndex, text.getString().getSize() - 1));
        cursorIndex--;
    } else if (unicode == DEL && cursorIndex < text.getString().getSize()) {
        text.setString(text.getString().substring(0, cursorIndex) +
                       text.getString().substring(
                           cursorIndex + 1, text.getString().getSize() - 1));
    } else if (unicode >= SPACE && unicode <= TILDA) {
        text.setString(text.getString().toAnsiString().insert(
            cursorIndex, std::string{static_cast<char>(unicode)}));
        cursorIndex++;
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
