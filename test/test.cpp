#include "application.h"
#include "color-manager.h"
#include "font-enum.h"
#include "margin.h"
#include "text-input.h"
#include "word.h"
#include <iostream>

int main() {

    auto input = new TextInput(UBUNTU_R);
    input->setBackgroundColor(ColorManager::getColor(SILVER));
    // input->setPosition(
    //     {Application::SCREEN_WIDTH / 3.f, Application::SCREEN_HEIGHT / 3.f});
    input->setLabel("Label:");
    input->setSubmitBehavior(
        [&input]() { input->setLabel(input->getString()); });
    Margin margin(input, 100.0f);
    Application::push(&margin);

    std::cout << margin.getGlobalBounds().left << std::endl;
    std::cout << margin.getGlobalBounds().top << std::endl;
    std::cout << margin.getGlobalBounds().left + margin.getGlobalBounds().width
              << std::endl;
    std::cout << margin.getGlobalBounds().top + margin.getGlobalBounds().height
              << std::endl;

    // auto input2 = new TextInput(UBUNTU_R);
    // input2->setBackgroundColor(ColorManager::getColor(SILVER));
    // input2->setPosition(
    //     {margin.getGlobalBounds().left,
    //      margin.getGlobalBounds().top + margin.getGlobalBounds().height});
    // input2->setLabel("Label2:");
    // input2->setSubmitBehavior(
    //     [&input2]() { input2->setLabel(input2->getString()); });
    // Application::push(input2);

    auto text = new Word();
    text->setText("Hello there");
    text->setIsHoverable(true);
    text->addPadding(5);
    text->setBackgroundColor(sf::Color::Red);
    text->setTextColor(sf::Color::White);
    Application::push(text);

    auto text2 = new Word();
    text2->setText("Bold text");
    text2->setIsHoverable(true);
    text2->addPadding(5);
    text2->setBackgroundColor(sf::Color::Green);
    text2->setTextColor(sf::Color::White);
    text2->setFont(UBUNTU_B);
    text2->setPosition(
        text->getGlobalBounds().left + text->getGlobalBounds().width,
        text->getGlobalBounds().top + text->getGlobalBounds().height);
    text2->setCharacterSize(50);
    Application::push(text2);

    auto text3 = new Word();
    text3->setText("Moreeeee");
    text3->setIsHoverable(true);
    text3->addPadding(20);
    text3->setBackgroundColor(sf::Color::Yellow);
    text3->setTextColor(sf::Color::White);
    text3->setFont(UBUNTU_R);
    text3->setPosition(
        text2->getGlobalBounds().left + text2->getGlobalBounds().width,
        text2->getGlobalBounds().top + text2->getGlobalBounds().height);
    text3->setCharacterSize(150);
    Application::push(text3);

    Application::run();

    return 0;
}
