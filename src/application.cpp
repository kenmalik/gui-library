#include "application.h"
#include "gui-component.h"
#include "history.h"

std::vector<Word> Application::words;
std::vector<GuiComponent *> Application::components;

void Application::run() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Window");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            for (GuiComponent *&i : components) {
                i->eventHandler(window, event);
            }
            History::eventHandler(window, event);
        }

        for (GuiComponent *&i : components) {
            i->update();
        }

        window.clear();
        for (GuiComponent *&i : components) {
            window.draw(*i);
        }

        window.display();
    }
}

void Application::push(GuiComponent *component) {
    components.push_back(component);
}
