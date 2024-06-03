#include "button.h"
#include "color-enum.h"
#include "color-manager.h"
#include "font-manager.h"
#include "mouse-event.h"
#include "state-enum.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

Button::Button() : Button(UBUNTU_R, {128, 64}) {}

Button::Button(FontEnum font, sf::Vector2f size) {
    text.setCharacterSize(32);
    text.setFont(FontManager::getFont(font));
    text.setFillColor(defaultTextColor);

    background.setSize(size);
    background.setFillColor(defaultButtonColor);
}

void Button::setPosition(sf::Vector2f position) {
    background.setPosition(position);
    auto bgBounds = background.getGlobalBounds();
    auto labelBounds = text.getGlobalBounds();
    text.setPosition(bgBounds.left + (bgBounds.width - labelBounds.width) / 2,
                     bgBounds.top + (bgBounds.height - labelBounds.height) / 2);
    text.move(text.getPosition().x - text.getGlobalBounds().left,
              text.getPosition().y - text.getGlobalBounds().top);
}

void Button::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (getState(DISABLED)) {
        return;
    }

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
        submit();
    } else {
        this->disableState(CLICKED);
    }

    if (MouseEvent::isClickedOff(
            getTransform().transformRect(background.getGlobalBounds()),
            window)) {
        this->disableState(FOCUSED);
    }
}

void Button::update() {
    if (this->getState(HOVERED)) {
        background.setFillColor(ColorManager::getColor(DIMGREY));
    } else {
        background.setFillColor(defaultButtonColor);
    }

    if (this->getState(CLICKED)) {
        background.setFillColor(sf::Color::Red);
    }

    if (this->getState(DISABLED)) {
        background.setFillColor(ColorManager::getColor(DIMGREY));
    }
}

void Button::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    states.transform *= getTransform();
    window.draw(background, states);
    window.draw(text, states);
}

Snapshot &Button::getSnapshot() { return snapshot; }

void Button::applySnapshot(const Snapshot &snapshot) {}

void Button::submit() { submitBehavior(); }

void Button::setSubmitBehavior(std::function<void()> submitBehavior) {
    this->submitBehavior = submitBehavior;
}

sf::FloatRect Button::getGlobalBounds() const {
    return background.getGlobalBounds();
}

void Button::setText(const std::string &string) { text.setString(string); }

const sf::String &Button::getText() const { return text.getString(); }

void Button::setTextSize(unsigned int size) { text.setCharacterSize(size); }

void Button::setTextColor(const sf::Color &color) { text.setFillColor(color); }

void Button::setBackgroundColor(const sf::Color &color) {
    defaultButtonColor = color;
    background.setFillColor(color);
}
