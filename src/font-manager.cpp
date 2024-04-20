#include "font-manager.h"

std::map<FontEnum, sf::Font> FontManager::fonts;

sf::Font &FontManager::getFont(FontEnum font) {
    if (fonts.count(font) == 0) {
        loadFont(font);
    }
    return fonts[font];
}

void FontManager::loadFont(FontEnum font) {
    if (!fonts[font].loadFromFile(getFontPath(font))) {
        exit(28);
    }
}

std::string FontManager::getFontPath(FontEnum font) {
    switch (font) {
    case UBUNTU_R:
        return "../fonts/Ubuntu-R.ttf";
    case UBUNTU_B:
        return "../fonts/Ubuntu-B.ttf";
    default:
        exit(28);
    }
}
