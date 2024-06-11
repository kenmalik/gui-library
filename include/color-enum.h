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
    {"silver", SILVER},
    {"dimgrey", DIMGREY},
    {"ghostwhite", GHOSTWHITE},
    {"yellow", YELLOW}};

#endif // !CS8_GUILIBRARY_COLORENUM_H
