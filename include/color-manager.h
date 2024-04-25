#ifndef CS8_GUILIBRARY_COLORMANAGER_H
#define CS8_GUILIBRARY_COLORMANAGER_H

#include "color-enum.h"
#include <SFML/Graphics/Color.hpp>
#include <map>

class ColorManager {
  public:
    static std::map<ColorEnum, sf::Color> colors;
    static sf::Color &getColor(ColorEnum color);
    static void loadColor(ColorEnum color);
    static sf::Color &getColorRGBA(ColorEnum color);
};

#endif // !CS8_GUILIBRARY_COLORMANAGER_H
