#ifndef CS8_GUILIBRARY_HISTORYNODE_H
#define CS8_GUILIBRARY_HISTORYNODE_H

#include "snapshot-interface.h"
#include "snapshot.h"

struct HistoryNode {
    Snapshot snapshot;
    SnapshotInterface *component;
};

#endif // !CS8_GUILIBRARY_HISTORYNODE_H
