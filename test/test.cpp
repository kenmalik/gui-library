#include "application.h"
#include "button.h"
#include "color-manager.h"
#include "font-enum.h"
#include "margin.h"
#include "padding.h"
#include "state-enum.h"
#include "text-input.h"
#include "word.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>

int main() {
    auto button = new Button();
    button->setBackgroundColor(sf::Color::Transparent);
    button->setText("Say Hello");
    button->setSubmitBehavior(
        []() { std::cout << "Hello, World!" << std::endl; });
    button->setPosition({300, 300});
    auto paddedButton = new Padding(button, 10);
    paddedButton->setBackgroundColor(sf::Color::Red);
    Application::push(paddedButton);

    auto text = new Word();
    text->setText("Hello there");
    text->setIsHoverable(true);
    text->setTextColor(sf::Color::Black);
    Application::push(text);

    auto text2 = new Word();
    text2->setText("Hello there");
    text2->setIsHoverable(true);
    text2->setTextColor(sf::Color::Black);
    auto pad2 = new Padding(text2, 10);
    pad2->setBackgroundColor(sf::Color::Red);
    pad2->setPosition(0, text->getGlobalBounds().top +
                             text->getGlobalBounds().height);
    Application::push(pad2);

    auto text3 = new Word();
    text3->setText("Hello there");
    text3->setIsHoverable(true);
    text3->setTextColor(sf::Color::Black);
    auto pad3 = new Padding(text3, 10);
    pad3->setBackgroundColor(sf::Color::Green);
    pad3->setPosition(0, pad2->getGlobalBounds().top +
                             pad2->getGlobalBounds().height);
    auto margin3 = new Margin(pad3, 50);
    Application::push(margin3);

    Application::run();

    return 0;
}
