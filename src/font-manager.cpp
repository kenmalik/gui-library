#include "font-manager.h"
#include "gui-lib-conf.h"

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
    std::string fontFile;
    switch (font) {
    case UBUNTU_R:
        fontFile = "Ubuntu-R.ttf";
        break;
    case UBUNTU_B:
        fontFile = "Ubuntu-B.ttf";
        break;
    default:
        exit(28);
    }
    return FONT_DIR_PATH + fontFile;
}
