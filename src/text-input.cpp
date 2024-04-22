#include "text-input.h"
#include "keyboard-shortcuts.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

TextInput::TextInput() : TextInput(UBUNTU_R, {360, 30}) {}

TextInput::TextInput(FontEnum font, sf::Vector2f size)
    : isCursorVisible(true), cursorIndex(0) {
    text.setCharacterSize(size.y * .8);
    text.setFont(FontManager::getFont(font));

    cursor.setFillColor(sf::Color::Red);
    cursor.setSize({2, static_cast<float>(size.y * .8)});

    background.setSize(size);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::White);
    background.setFillColor(sf::Color::Cyan);
}

void TextInput::setString(const std::string &string) {
    text.setString(string);
    cursorIndex = text.getString().getSize();
    moveCursor();
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
            moveCursor();
        }
        if (event.key.code == sf::Keyboard::Right &&
            cursorIndex < text.getString().getSize()) {
            cursorIndex++;
            moveCursor();
        }
    }

    if (KeyboardShortcuts::isUndo()) {
        setString("");
    }
}

void TextInput::handleTextInput(unsigned int unicode) {
    if (unicode == BACKSPACE && cursorIndex > 0) {
        text.setString(text.getString().substring(0, cursorIndex - 1) +
                       text.getString().substring(
                           cursorIndex, text.getString().getSize() - 1));
        cursorIndex--;
        moveCursor();
    } else if (unicode == DEL && cursorIndex < text.getString().getSize()) {
        text.setString(text.getString().substring(0, cursorIndex) +
                       text.getString().substring(
                           cursorIndex + 1, text.getString().getSize() - 1));
    } else if (unicode >= SPACE && unicode <= TILDA) {
        text.setString(text.getString().toAnsiString().insert(
            cursorIndex, std::string{static_cast<char>(unicode)}));
        cursorIndex++;
        moveCursor();
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

    if (cursorTimer.getElapsedTime() >=
        sf::milliseconds(isCursorVisible ? CURSOR_BLINK_ON
                                         : CURSOR_BLINK_OFF)) {
        isCursorVisible = !isCursorVisible;
        cursorTimer.restart();
    }
}

void TextInput::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    window.draw(background);
    window.draw(text);
    if (isCursorVisible) {
        window.draw(cursor);
    }
}

Snapshot &TextInput::getSnapshot() { return snapshot; }

void TextInput::applySnapshot(const Snapshot &snapshot) {}

void TextInput::moveCursor() {
    cursor.setPosition(text.findCharacterPos(cursorIndex).x,
                       background.getGlobalBounds().top +
                           background.getGlobalBounds().height * .15);
    isCursorVisible = true;
    cursorTimer.restart();
}
