#ifndef CS8_GUILIBRARY_HISTORYNODE_H
#define CS8_GUILIBRARY_HISTORYNODE_H

#include "gui-component.h"
#include "snapshot.h"

struct HistoryNode {
    Snapshot snapshot;
    GuiComponent *component;
};

#endif // !CS8_GUILIBRARY_HISTORYNODE_H
