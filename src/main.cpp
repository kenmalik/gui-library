#include "application.h"
#include "color-manager.h"
#include "font-enum.h"
#include "text-input.h"

int main() {
    auto input = new TextInput(UBUNTU_R);
    input->setBackgroundColor(ColorManager::getColor(SILVER));
    input->setPosition(
        {Application::SCREEN_WIDTH / 3.f, Application::SCREEN_HEIGHT / 3.f});
    input->setLabel("Label:");
    input->setSubmitBehavior(
        [&input]() { input->setLabel(input->getString()); });

    Application::push(input);

    Application::run();

    return 0;
}
