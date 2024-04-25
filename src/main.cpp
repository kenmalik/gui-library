#include "application.h"
#include "color-manager.h"
#include "font-enum.h"
#include "text-input.h"

int main() {
    auto input = new TextInput(UBUNTU_B);
    input->setBackgroundColor(ColorManager::getColor(SILVER));
    input->setPosition(
        {Application::kScreenWidth / 3.f, Application::kScreenHeight / 3.f});

    Application::push(input);

    Application::run();

    return 0;
}
