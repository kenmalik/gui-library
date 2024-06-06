#include "application.h"
#include "button.h"
#include "composite-gui-component.h"
#include "margin.h"
#include "padding.h"
#include "state-enum.h"
#include "text-input.h"
#include "word.h"
#include <SFML/Graphics/Color.hpp>
#include <iostream>

void originalTest();
void compositeTest();

int main() {
    compositeTest();

    Application::run();

    return 0;
}

void originalTest() {
    auto button = new Button();
    button->setText("Say Hello");
    button->setSubmitBehavior(
        []() { std::cout << "Hello, World!" << std::endl; });
    button->setPosition({300, 300});
    auto paddedButton = new Padding(button, 10);
    paddedButton->setBackgroundColor(sf::Color::Red);
    Application::push(paddedButton);
    std::cout << "Padded Button (bottom left):" << std::endl;
    std::cout << "x: " << paddedButton->getGlobalBounds().left << "\ny: "
              << paddedButton->getGlobalBounds().top +
                     paddedButton->getGlobalBounds().height
              << std::endl;

    auto input = new TextInput();
    auto paddedInput = new Padding(input, 30);
    paddedInput->setBackgroundColor(sf::Color::Yellow);
    auto marginedInput = new Margin(paddedInput, 20);
    Application::push(marginedInput);
    std::cout << "Text Input:" << std::endl;
    std::cout << "x: " << input->getGlobalBounds().left
              << "\ny: " << input->getGlobalBounds().top << std::endl;

    auto fakeInput = new Word();
    fakeInput->setText("Should be");
    fakeInput->setPosition(0, marginedInput->getGlobalBounds().top +
                                  marginedInput->getGlobalBounds().height);
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

    bool disabled = false;
    auto disableButton = new Button();
    disableButton->setText("Disable");
    disableButton->setSubmitBehavior([&disabled, &input, &button]() {
        if (disabled) {
            input->disableState(DISABLED);
            button->disableState(DISABLED);
        } else {
            input->enableState(DISABLED);
            button->enableState(DISABLED);
        }
        disabled = !disabled;
    });
    disableButton->setPosition({paddedButton->getGlobalBounds().left,
                                paddedButton->getGlobalBounds().top +
                                    paddedButton->getGlobalBounds().height});
    auto paddedDisableButton = new Padding(disableButton, 10);
    paddedDisableButton->setBackgroundColor(sf::Color::Red);
    auto marginedDisable = new Margin(paddedDisableButton, 20, 80);
    std::cout << "Padded Disable (top left):" << std::endl;
    std::cout << "x: " << paddedDisableButton->getGlobalBounds().left
              << "\ny: " << paddedDisableButton->getGlobalBounds().top
              << std::endl;
    std::cout << "Margined Disable (top left):" << std::endl;
    std::cout << "x: " << marginedDisable->getGlobalBounds().left
              << "\ny: " << marginedDisable->getGlobalBounds().top << std::endl;

    auto words = new Word();
    words->setText("Click above");
    words->setPosition(marginedDisable->getGlobalBounds().left,
                       marginedDisable->getGlobalBounds().top +
                           marginedDisable->getGlobalBounds().height);
    auto marginWords = new Margin(words, 10, 80);

    auto moreWords = new Word();
    moreWords->setText("More words");
    moreWords->setPosition(marginWords->getGlobalBounds().left,
                           marginWords->getGlobalBounds().top +
                               marginWords->getGlobalBounds().height);
    auto marginMoreWords = new Margin(moreWords, 0, 80);

    auto composite = new CompositeGUIComponent();
    composite->addChild(marginedDisable);
    composite->addChild(marginWords);
    composite->addChild(marginMoreWords);
    std::cout << "Composite" << std::endl;
    std::cout << "x: " << composite->getGlobalBounds().left
              << "\ny: " << composite->getGlobalBounds().top << std::endl;
    // Application::push(composite);

    auto padComposite = new Padding(composite, 20, 80);
    padComposite->setBackgroundColor(sf::Color::Green);
    // Application::push(padComposite);

    auto marginComposite = new Margin(padComposite, 20, 80);
    Application::push(marginComposite);

    std::cout << "Child iterator test" << std::endl;
    CompositeGUIComponent::childIterator iter;
    for (iter = composite->childrenBegin(); iter != composite->childrenEnd();
         iter++) {
        std::cout << "Top: " << (*iter)->getGlobalBounds().top << std::endl;
    }
}

void compositeTest() {
    auto composite = new CompositeGUIComponent();

    auto word0 = new Word();
    word0->setText("Hello from word 0");
    word0->setPosition(0, 0);

    auto word1 = new Word();
    word1->setText("Hello from word 1");
    word1->setPosition(0, 50);

    auto word2 = new Word();
    word2->setText("Hello from word 2");
    word2->setPosition(0, 100);

    auto word3 = new Word();
    word3->setText("Hello from word 3");
    word3->setPosition(0, 150);

    composite->addChild(word0);
    composite->addChild(word1);
    composite->addChild(word2);
    composite->addChild(word3);

    Application::push(composite);
}
