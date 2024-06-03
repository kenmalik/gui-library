#include "application.h"
#include "button.h"
#include "margin.h"
#include "padding.h"
#include "state-enum.h"
#include "text-input.h"
#include "word.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>

int main() {
    auto button = new Button();
    button->setText("Say Hello");
    button->setSubmitBehavior(
        []() { std::cout << "Hello, World!" << std::endl; });
    button->setPosition({300, 300});
    auto paddedButton = new Padding(button, 10);
    paddedButton->setBackgroundColor(sf::Color::Red);
    Application::push(paddedButton);

    auto input = new TextInput();
    auto paddedInput = new Padding(input, 30);
    paddedInput->setBackgroundColor(sf::Color::Yellow);
    Application::push(paddedInput);
    std::cout << "Text Input:" << std::endl;
    std::cout << "x: " << input->getGlobalBounds().left
              << "\ny: " << input->getGlobalBounds().top << std::endl;

    auto fakeInput = new Word();
    fakeInput->setText("Should be");
    fakeInput->setPosition(0, paddedInput->getGlobalBounds().top +
                                  paddedInput->getGlobalBounds().height);
    auto paddedFake = new Padding(fakeInput, 30);
    paddedFake->setBackgroundColor(sf::Color::Yellow);
    Application::push(paddedFake);

    auto text = new Word();
    text->setText("Hello there");
    text->setIsHoverable(true);
    text->setTextColor(sf::Color::Black);
    text->setPosition(0, paddedFake->getGlobalBounds().top +
                             paddedFake->getGlobalBounds().height);
    Application::push(text);

    auto text2 = new Word();
    text2->setText("Hello there");
    text2->setIsHoverable(true);
    text2->setTextColor(sf::Color::Black);
    auto pad2 = new Padding(text2, 10, 50);
    pad2->setBackgroundColor(sf::Color::Red);
    pad2->setPosition(0, text->getGlobalBounds().top +
                             text->getGlobalBounds().height);
    Application::push(pad2);

    auto text3 = new Word();
    text3->setText("Hello there");
    text3->setIsHoverable(true);
    text3->setTextColor(sf::Color::Black);
    auto pad3 = new Padding(text3, 10, 30);
    pad3->setBackgroundColor(sf::Color::Green);
    pad3->setPosition(0, pad2->getGlobalBounds().top +
                             pad2->getGlobalBounds().height);
    auto margin3 = new Margin(pad3, 30, 50);
    Application::push(margin3);

    auto disableButton = new Button();
    disableButton->setText("Disable");
    disableButton->setSubmitBehavior([&input, &button]() {
        input->enableState(DISABLED);
        button->enableState(DISABLED);
    });
    disableButton->setPosition(
        {button->getGlobalBounds().left,
         button->getGlobalBounds().top + button->getGlobalBounds().height});
    auto paddedDisableButton = new Padding(disableButton, 10);
    paddedDisableButton->setBackgroundColor(sf::Color::Red);
    Application::push(paddedDisableButton);

    Application::run();

    return 0;
}
