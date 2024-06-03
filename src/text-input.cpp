#include "text-input.h"
#include "color-enum.h"
#include "color-manager.h"
#include "font-manager.h"
#include "history.h"
#include "mouse-event.h"
#include "state-enum.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

TextInput::TextInput() : TextInput(UBUNTU_R, {360, 30}) {}

TextInput::TextInput(FontEnum font, sf::Vector2f size)
    : isCursorVisible(false), cursorIndex(0) {
    label.setCharacterSize(size.y * .8);
    label.setFont(FontManager::getFont(font));
    label.setFillColor(sf::Color::White);

    background.setSize(size);
    background.setOutlineThickness(2);
    background.setOutlineColor(ColorManager::getColor(DIMGREY));

    text.setCharacterSize(size.y * .8);
    text.setFont(FontManager::getFont(font));
    text.setFillColor(sf::Color::Black);

    cursor.setFillColor(sf::Color::Black);
    cursor.setSize({2, size.y * .8f});

    moveTextBox();

    History::pushHistory({text.getString().toAnsiString(), this});
}

void TextInput::setPosition(sf::Vector2f position) {
    label.setPosition(position);
    moveTextBox();
}

void TextInput::setString(const std::string &string) {
    text.setString(string);
    cursorIndex = text.getString().getSize();
    moveCursor();
}

void TextInput::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (MouseEvent::isHovered(
            getTransform().transformRect(background.getGlobalBounds()),
            window)) {
        this->enableState(HOVERED);
    } else {
        this->disableState(HOVERED);
    }

    if (MouseEvent::isClicked(
            getTransform().transformRect(background.getGlobalBounds()),
            window)) {
        this->enableState(CLICKED);
        this->enableState(FOCUSED);
    } else {
        this->disableState(CLICKED);
    }

    if (MouseEvent::isClickedOff(
            getTransform().transformRect(background.getGlobalBounds()),
            window)) {
        this->disableState(FOCUSED);
    }

    if (getState(FOCUSED)) {
        if (event.type == sf::Event::TextEntered &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            handleTextInput(event.text.unicode);
            History::pushHistory({text.getString().toAnsiString(), this});
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
            if (event.key.code == sf::Keyboard::Enter) {
                submit();
            }
        }
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
        background.setFillColor(ColorManager::getColor(DIMGREY));
    } else {
        background.setFillColor(sf::Color::White);
    }

    if (this->getState(CLICKED)) {
        background.setFillColor(sf::Color::Red);
    }

    if (this->getState(FOCUSED) &&
        cursorTimer.getElapsedTime() >=
            sf::milliseconds(isCursorVisible ? CURSOR_BLINK_ON
                                             : CURSOR_BLINK_OFF)) {
        isCursorVisible = !isCursorVisible;
        cursorTimer.restart();
    }
}

void TextInput::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(label, states);
    window.draw(background, states);
    window.draw(text, states);
    if (this->getState(FOCUSED) && isCursorVisible) {
        window.draw(cursor, states);
    }
}

Snapshot &TextInput::getSnapshot() { return snapshot; }

void TextInput::applySnapshot(const Snapshot &snapshot) {
    setString(snapshot.getData());
}

void TextInput::moveCursor() {
    float xPos = text.getString() == "" ? background.getPosition().x +
                                              background.getOutlineThickness()
                                        : text.findCharacterPos(cursorIndex).x;
    cursor.setPosition(xPos, background.getGlobalBounds().top +
                                 background.getGlobalBounds().height * .15);
    isCursorVisible = true;
    cursorTimer.restart();
}

void TextInput::moveTextBox() {
    background.setPosition(label.getGlobalBounds().left +
                               label.getGlobalBounds().width +
                               (label.getString() == "" ? 0 : 10),
                           label.getPosition().y);
    text.setPosition(background.getGlobalBounds().left +
                         background.getOutlineThickness() * 2,
                     background.getGlobalBounds().top);
    moveCursor();
}

void TextInput::setBackgroundColor(const sf::Color &color) {
    background.setFillColor(color);
}

void TextInput::setLabel(const std::string &string) {
    label.setString(string);
    moveTextBox();
}

void TextInput::submit() { submitBehavior(); }

const sf::String &TextInput::getString() const { return text.getString(); }

const sf::String &TextInput::getLabel() const { return label.getString(); }

void TextInput::setSubmitBehavior(std::function<void()> submitBehavior) {
    this->submitBehavior = submitBehavior;
}

sf::FloatRect TextInput::getGlobalBounds() const {
    sf::FloatRect localBounds(
        label.getGlobalBounds().left, background.getGlobalBounds().top,
        label.getGlobalBounds().width + background.getGlobalBounds().width,
        background.getGlobalBounds().height);
    return getTransform().transformRect(localBounds);
}
