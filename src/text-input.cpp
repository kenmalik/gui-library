#include "text-input.h"
#include "font-manager.h"
#include "history.h"
#include "mouse-event.h"
#include "state-enum.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

TextInput::TextInput() : TextInput(UBUNTU_R, {360, 30}) {}

TextInput::TextInput(FontEnum font, sf::Vector2f size)
    : isCursorVisible(false), cursorIndex(0) {
    boundingBox.width = size.x;
    boundingBox.height = size.y;

    text.setCharacterSize(size.y);
    text.setFont(FontManager::getFont(font));
    text.setFillColor(sf::Color::Black);

    cursor.setFillColor(sf::Color::Black);
    cursor.setSize({2, size.y});

    History::pushHistory({text.getString().toAnsiString(), this});
}

void TextInput::setString(const std::string &string) {
    text.setString(string);
    cursorIndex = text.getString().getSize();
    moveCursor();
}

void TextInput::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (this->getState(DISABLED)) {
        return;
    }

    if (MouseEvent::isHovered(getHitbox(), window)) {
        this->enableState(HOVERED);
    } else {
        this->disableState(HOVERED);
    }

    if (MouseEvent::isClicked(getHitbox(), window)) {
        this->enableState(CLICKED);
        this->enableState(FOCUSED);
    } else {
        this->disableState(CLICKED);
    }

    if (MouseEvent::isClickedOff(getHitbox(), window)) {
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
    if (this->getState(DISABLED)) {
        text.setFillColor(disabledTextColor);
        return;
    }

    if (this->getState(HOVERED)) {
        text.setFillColor(hoveredTextColor);
    } else {
        text.setFillColor(defaultTextColor);
    }

    if (this->getState(CLICKED)) {
        text.setFillColor(clickedTextColor);
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
    window.draw(text, states);
    if (!this->getState(DISABLED) && this->getState(FOCUSED) &&
        isCursorVisible) {
        window.draw(cursor, states);
    }
}

Snapshot &TextInput::getSnapshot() { return snapshot; }

void TextInput::applySnapshot(const Snapshot &snapshot) {
    setString(snapshot.getData());
}

void TextInput::moveCursor() {
    float xPos = text.findCharacterPos(cursorIndex).x;
    cursor.setPosition(xPos, text.getPosition().y);
    isCursorVisible = true;
    cursorTimer.restart();
}

void TextInput::submit() { submitBehavior(); }

const sf::String &TextInput::getString() const { return text.getString(); }

void TextInput::setSubmitBehavior(std::function<void()> submitBehavior) {
    this->submitBehavior = submitBehavior;
}

sf::FloatRect TextInput::getGlobalBounds() const {
    return getTransform().transformRect(boundingBox);
}

sf::FloatRect TextInput::getHitbox() const { return hitboxBehavior(); }

void TextInput::setHitboxBehavior(
    std::function<sf::FloatRect()> hitboxBehavior) {
    this->hitboxBehavior = hitboxBehavior;
}

sf::Transform TextInput::getParentTransfrom() const { return parentTransform; }

void TextInput::setParentTransfrom(const sf::Transform &transform) {
    parentTransform = transform;
}
