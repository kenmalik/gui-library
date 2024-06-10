#ifndef CS8_GUILIBRARY_TEXTINPUT_H
#define CS8_GUILIBRARY_TEXTINPUT_H

#include "color-enum.h"
#include "color-manager.h"
#include "font-enum.h"
#include "gui-component.h"
#include "snapshot-interface.h"
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
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>

class TextInput : public State,
                  public GuiComponent,
                  public Submitable,
                  public SnapshotInterface {
  public:
    TextInput();
    TextInput(FontEnum font, sf::Vector2f size = {360, 30});

    const sf::String &getString() const;
    void setString(const std::string &string);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;

    Snapshot &getSnapshot() override;
    void applySnapshot(const Snapshot &snapshot) override;

    void setSubmitBehavior(std::function<void()> submitBehavior);

    sf::FloatRect getGlobalBounds() const override;
    sf::FloatRect getLocalBounds() const;

    void setHitboxBehavior(std::function<sf::FloatRect()>) override;
    sf::FloatRect getHitbox() const override;

    sf::Transform getParentTransfrom() const override;
    void setParentTransfrom(const sf::Transform &transform) override;

  private:
    static constexpr unsigned int BACKSPACE = 8;
    static constexpr unsigned int DEL = 127;
    static constexpr unsigned int SPACE = 32;
    static constexpr unsigned int TILDA = 126;

    static constexpr unsigned int CURSOR_BLINK_ON = 450;
    static constexpr unsigned int CURSOR_BLINK_OFF = 450;
    sf::Clock cursorTimer;
    bool isCursorVisible;

    sf::Color defaultTextColor = sf::Color::Black;
    sf::Color disabledTextColor = ColorManager::getColor(DIMGREY);
    sf::Color hoveredTextColor = ColorManager::getColor(DIMGREY);
    sf::Color clickedTextColor = sf::Color::Blue;

    sf::Transform parentTransform = sf::Transform::Identity;

    sf::FloatRect boundingBox;

    size_t cursorIndex;
    sf::RectangleShape cursor;

    sf::Text text;

    Snapshot snapshot;

    void handleTextInput(unsigned int unicode);
    void moveCursor();

    void submit() override;
    std::function<void()> submitBehavior = []() {};
    std::function<sf::FloatRect()> hitboxBehavior =
        std::bind(&TextInput::getGlobalBounds, this);
};

#endif // !CS8_GUILIBRARY_TEXTINPUT_H
