#ifndef CS8_GUILIBRARY_BUTTON_H
#define CS8_GUILIBRARY_BUTTON_H

#include "font-enum.h"
#include "gui-component.h"
#include "snapshot.h"
#include "states.h"
#include "submittable.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>

class Button : public State, public GuiComponent, public Submitable {
  public:
    Button();
    Button(FontEnum font, sf::Vector2f size = {128, 64});

    const sf::String &getText() const;
    void setText(const std::string &string);
    void setTextSize(unsigned int size);
    void setTextColor(const sf::Color &color);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;

    Snapshot &getSnapshot() override;
    void applySnapshot(const Snapshot &snapshot) override;

    void setBackgroundColor(const sf::Color &color);
    void setPosition(sf::Vector2f position);
    void setSubmitBehavior(std::function<void()> submitBehavior);

    sf::FloatRect getGlobalBounds() const override;

  private:
    sf::Color defaultButtonColor = sf::Color::Black;
    sf::Color defaultTextColor = sf::Color::White;

    sf::Text text;
    sf::RectangleShape background;

    Snapshot snapshot;

    void submit() override;
    std::function<void()> submitBehavior;
};

#endif // !CS8_GUILIBRARY_BUTTON_H
