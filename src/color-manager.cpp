#include "color-manager.h"
#include "color-enum.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

std::map<ColorEnum, sf::Color> ColorManager::colors;

sf::Color &ColorManager::getColor(std::string color) {
    try {
        return getColor(COLOR_MAP.at(color));
    } catch (std::out_of_range &e) {
        std::cerr << "Invalid color string\n" << e.what() << std::endl;
        exit(1);
    }
}
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
    case GHOSTWHITE:
        colors[color] = sf::Color(248, 248, 255);
        break;
    case YELLOW:
        colors[color] = sf::Color(255, 255, 0);
        break;
    case MAROON:
        colors[color] = sf::Color(128, 0, 0);
        break;
    case RED:
        colors[color] = sf::Color(255, 0, 0);
        break;
    case WHITE:
        colors[color] = sf::Color(255, 255, 255);
        break;
    case PURPLE:
        colors[color] = sf::Color(128, 0, 128);
        break;
    case GRAY:
        colors[color] = sf::Color(128, 128, 128);
        break;
    case FUCHSIA:
        colors[color] = sf::Color(255, 0, 255);
        break;
    case GREEN:
        colors[color] = sf::Color(0, 128, 0);
        break;
    case LIME:
        colors[color] = sf::Color(0, 255, 0);
        break;
    case OLIVE:
        colors[color] = sf::Color(128, 128, 0);
        break;
    case NAVY:
        colors[color] = sf::Color(0, 0, 128);
        break;
    case BLUE:
        colors[color] = sf::Color(0, 0, 255);
        break;
    case TEAL:
        colors[color] = sf::Color(0, 128, 128);
        break;
    case AQUA:
        colors[color] = sf::Color(0, 255, 255);
        break;
    default:
        exit(28);
    }
}
