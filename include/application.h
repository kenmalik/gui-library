#ifndef CS8_GUILIBRARY_APPLICATION_H
#define CS8_GUILIBRARY_APPLICATION_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "gui-component.h"
#include "word.h"
#include <vector>

class Application {
  public:
    static void run();
    static void push(GuiComponent *component);
    static void push(const Word &word);

    static constexpr int SCREEN_WIDTH = 1200;
    static constexpr int SCREEN_HEIGHT = 800;

  private:
    static std::vector<GuiComponent *> components;
    static std::vector<Word> words;
};

#endif // !CS8_GUILIBRARY_APPLICATION_H
