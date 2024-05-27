#ifndef CS8_GUILIBRARY_GUICOMPONENT_H
#define CS8_GUILIBRARY_GUICOMPONENT_H

#include "bounded.h"
#include "event-hander.h"
#include "snapshot-interface.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>

class GuiComponent : public sf::Drawable,
                     public EventHandler,
                     public SnapshotInterface,
                     public sf::Transformable,
                     public Bounded {
  public:
    virtual void draw(sf::RenderTarget &window,
                      sf::RenderStates states) const override = 0;

    virtual void eventHandler(sf::RenderWindow &window,
                              sf::Event event) override = 0;
    virtual void update() override = 0;

    virtual Snapshot &getSnapshot() override = 0;
    virtual void applySnapshot(const Snapshot &snapshot) override = 0;
    virtual sf::FloatRect getGlobalBounds() const override = 0;
};

#endif // CS8_GUILIBRARY_GUICOMPONENT_H
