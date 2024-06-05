#ifndef CS8_GUILIBRARY_GUICOMPONENTDECORATOR_H
#define CS8_GUILIBRARY_GUICOMPONENTDECORATOR_H

#include "gui-component.h"

class GUIComponentDecorator : public GuiComponent {
  public:
    GUIComponentDecorator(GuiComponent *component);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;

    GuiComponent *component;
};

#endif // !CS8_GUILIBRARY_GUICOMPONENTDECORATOR_H
