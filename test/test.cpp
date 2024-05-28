#include "application.h"
#include "color-manager.h"
#include "font-enum.h"
#include "margin.h"
#include "text-input.h"
#include "word.h"
#include <SFML/Graphics/Color.hpp>
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
    text->setPadding(5);
    text->setBackgroundColor(sf::Color::Red);
    text->setTextColor(sf::Color::White);
    Application::push(text);

    auto text2 = new Word();
    text2->setText("Bold text");
    text2->setIsHoverable(true);
    text2->setPadding(5);
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
    text3->setPadding(20);
    text3->setBackgroundColor(sf::Color::Yellow);
    text3->setTextColor(sf::Color::White);
    text3->setFont(UBUNTU_R);
    text3->setPosition(
        text2->getGlobalBounds().left + text2->getGlobalBounds().width,
        text2->getGlobalBounds().top + text2->getGlobalBounds().height);
    Application::push(text3);

    auto text4 = new Word();
    text4->setText("Text 4");
    text4->setIsHoverable(true);
    text4->setPadding(10, 50);
    text4->setBackgroundColor(sf::Color::Black);
    text4->setTextColor(sf::Color::White);
    text4->setFont(UBUNTU_B);
    text4->setPosition(0, text3->getGlobalBounds().top +
                              text3->getGlobalBounds().height);
    Application::push(text4);

    auto text5 = new Word();
    text5->setText("Text 5");
    text5->setIsHoverable(true);
    text5->setPadding(10, 50);
    text5->setBackgroundColor(sf::Color::Cyan);
    text5->setTextColor(sf::Color::White);
    text5->setFont(UBUNTU_R);
    text5->setPosition(0, text4->getGlobalBounds().top +
                              text4->getGlobalBounds().height);
    Application::push(text5);

    auto text6 = new Word();
    text6->setText("Text 6");
    text6->setIsHoverable(true);
    text6->setPadding(10, 50, 30);
    text6->setBackgroundColor(sf::Color::Green);
    text6->setTextColor(sf::Color::White);
    text6->setFont(UBUNTU_R);
    text6->setPosition(0, text5->getGlobalBounds().top +
                              text5->getGlobalBounds().height);
    Application::push(text6);

    auto text7 = new Word();
    text7->setText("Text 7");
    text7->setIsHoverable(true);
    text7->setPadding(10, 50, 30, 0);
    text7->setBackgroundColor(sf::Color::Red);
    text7->setTextColor(sf::Color::White);
    text7->setFont(UBUNTU_R);
    text7->setPosition(0, text6->getGlobalBounds().top +
                              text6->getGlobalBounds().height);
    Application::push(text7);

    Application::run();

    return 0;
}
