#ifndef CS8_GUILIBRARY_COLORENUM_H
#define CS8_GUILIBRARY_COLORENUM_H

#include <map>
#include <string>

enum ColorEnum {
    SILVER,
    DIMGREY,
    GHOSTWHITE,
    YELLOW,
    MAROON,
    RED,
    WHITE,
    PURPLE,
    GRAY,
    FUCHSIA,
    GREEN,
    LIME,
    OLIVE,
    NAVY,
    BLUE,
    TEAL,
    AQUA
};

static const std::map<std::string, ColorEnum> COLOR_MAP = {
    {"silver", SILVER},   {"dimgrey", DIMGREY}, {"ghostwhite", GHOSTWHITE},
    {"yellow", YELLOW},   {"maroon", MAROON},   {"red", RED},
    {"white", WHITE},     {"purple", PURPLE},   {"gray", GRAY},
    {"fuchsia", FUCHSIA}, {"green", GREEN},     {"lime", LIME},
    {"olive", OLIVE},     {"navy", NAVY},       {"blue", BLUE},
    {"teal", TEAL},       {"aqua", AQUA},
};

#endif // !CS8_GUILIBRARY_COLORENUM_H
