#include "application.h"
#include "font-enum.h"

int main() {
    Word word(UBUNTU_R);
    word.setString("Word");

    TextInput input(UBUNTU_B);
    input.setString("Input");

    for (int i = 0; i < 10; i++) {
        Word w = word;
        w.setPosition(sf::Vector2f(rand() % Application::kScreenWidth,
                                   rand() % Application::kScreenHeight));
        Application::push(w);
    }

    Application::push(input);

    Application::run();

    return 0;
}
