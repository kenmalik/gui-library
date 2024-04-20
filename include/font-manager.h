#ifndef CS8_GUILIBRARY_FONTMANAGER_H
#define CS8_GUILIBRARY_FONTMANAGER_H

#include "font-enum.h"

#include <SFML/Graphics/Font.hpp>
#include <map>

class FontManager {
  public:
    static sf::Font &getFont(FontEnum font);

  private:
    static std::map<FontEnum, sf::Font> fonts;
    static void loadFont(FontEnum font);
    static std::string getFontPath(FontEnum font);
};

#endif // !CS8_GUILIBRARY_FONTMANAGER_H
