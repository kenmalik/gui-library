#include "application.h"
#include "gui-component.h"
#include "history.h"
#include "text-input.h"

std::vector<Word> Application::words;
std::vector<GuiComponent *> Application::components;

void Application::run() {
    sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight),
                            "Window");
    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            for (Word &w : words) {
                w.eventHandler(window, event);
            }
            for (GuiComponent *&i : components) {
                i->eventHandler(window, event);
            }
            History::eventHandler(window, event);
        }

        for (Word &w : words) {
            w.update();
        }

        for (GuiComponent *&i : components) {
            i->update();
        }

        window.clear();
        for (Word &w : words) {
            window.draw(w);
        }
        for (GuiComponent *&i : components) {
            window.draw(*i);
        }

        window.display();
    }
}

void Application::push(GuiComponent *component) {
    components.push_back(component);
}

void Application::push(const Word &word) { words.push_back(word); }
