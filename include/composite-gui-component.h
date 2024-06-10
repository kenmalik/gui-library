#ifndef CS8_GUILIBRARY_COMPOSITEGUICOMPONENT_H
#define CS8_GUILIBRARY_COMPOSITEGUICOMPONENT_H

#include "gui-component.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <functional>
#include <vector>

class CompositeGUIComponent : public GuiComponent {
  public:
    typedef std::vector<GuiComponent *>::iterator childIterator;

    CompositeGUIComponent();

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;

    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void setHitboxBehavior(std::function<sf::FloatRect()>) override;
    virtual sf::FloatRect getHitbox() const override;

    void addChild(GuiComponent *component);

    childIterator childrenBegin();
    childIterator childrenEnd();
    bool childrenEmpty() const;

    sf::Transform getParentTransfrom() const override;
    void setParentTransfrom(const sf::Transform &transform) override;

    void resetOrigin();

  private:
    sf::Transform parentTransform = sf::Transform::Identity;

    std::vector<GuiComponent *> children;

    std::function<sf::FloatRect()> hitboxBehavior =
        std::bind(&CompositeGUIComponent::getGlobalBounds, this);

    sf::FloatRect getChildBounds() const;
    sf::Transform getTotalTransform() const;
};

#endif // !CS8_GUILIBRARY_COMPOSITEGUICOMPONENT_H
