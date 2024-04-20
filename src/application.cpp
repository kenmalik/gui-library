#include "application.h"
#include "text-input.h"

std::vector<Word> Application::words;
std::vector<TextInput> Application::inputs;

void Application::run() {
    sf::CircleShape circle(100);

    sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight),
                            "Window");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            for (Word &w : words) {
                w.eventHandler(window, event);
            }
            for (TextInput &i : inputs) {
                i.eventHandler(window, event);
            }
        }

        for (Word &w : words) {
            w.update();
        }

        for (TextInput &i : inputs) {
            i.update();
        }

        window.clear();
        for (Word &w : words) {
            window.draw(w);
        }
        for (TextInput &i : inputs) {
            window.draw(i);
        }

        window.display();
    }
}

void Application::push(const Word &word) { words.push_back(word); }

void Application::push(const TextInput &input) { inputs.push_back(input); }
