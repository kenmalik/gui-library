#include "button.h"
#include "font-manager.h"
#include "mouse-event.h"
#include "state-enum.h"

#include <SFML/Window/Keyboard.hpp>

Button::Button() : Button(UBUNTU_R, {128, 64}) {}

Button::Button(FontEnum font, sf::Vector2f size) {
    text.setCharacterSize(32);
    text.setFont(FontManager::getFont(font));
    text.setFillColor(defaultTextColor);
}

void Button::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (getState(DISABLED)) {
        return;
    }

    if (MouseEvent::isHovered(getGlobalBounds(), window)) {
        this->enableState(HOVERED);
    } else {
        this->disableState(HOVERED);
    }

    if (MouseEvent::isClicked(getGlobalBounds(), window)) {
        this->enableState(CLICKED);
        this->enableState(FOCUSED);
        submit();
    } else {
        this->disableState(CLICKED);
    }

    if (MouseEvent::isClickedOff(getGlobalBounds(), window)) {
        this->disableState(FOCUSED);
    }
}

void Button::update() {
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
}

void Button::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(text, states);
}

Snapshot &Button::getSnapshot() { return snapshot; }

void Button::applySnapshot(const Snapshot &snapshot) {}

void Button::submit() { submitBehavior(); }

void Button::setSubmitBehavior(std::function<void()> submitBehavior) {
    this->submitBehavior = submitBehavior;
}

sf::FloatRect Button::getGlobalBounds() const {
    return getTransform().transformRect(text.getGlobalBounds());
}

void Button::setText(const std::string &string) { text.setString(string); }

const sf::String &Button::getText() const { return text.getString(); }

void Button::setTextSize(unsigned int size) { text.setCharacterSize(size); }

void Button::setTextColor(const sf::Color &color) { text.setFillColor(color); }
