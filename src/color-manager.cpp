#include "color-manager.h"
#include "color-enum.h"
#include <cstdlib>

std::map<ColorEnum, sf::Color> ColorManager::colors;

sf::Color &ColorManager::getColor(ColorEnum color) {
    if (colors.count(color) == 0) {
        loadColor(color);
    }
    return colors[color];
}

void ColorManager::loadColor(ColorEnum color) {
    switch (color) {
    case SILVER:
        colors[color] = sf::Color(192, 192, 192);
        break;
    case DIMGREY:
        colors[color] = sf::Color(105, 105, 105);
        break;
    default:
        exit(28);
    }
}
