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
    //
    auto text = new Word();
    text->setText("Hello there");
    text->setIsHoverable(true);
    text->addPadding(50);
    Application::push(text);

    Application::run();

    return 0;
}
