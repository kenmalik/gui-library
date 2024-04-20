#ifndef CS8_GUILIBRARY_SNAPSHOTINTERFACE_H
#define CS8_GUILIBRARY_SNAPSHOTINTERFACE_H

#include "snapshot.h"

class SnapshotInterface {
  public:
    virtual Snapshot &getSnapshot() = 0;
    virtual void applySnapshot(const Snapshot &snapshot) = 0;
};

#endif // CS8_GUILIBRARY_SNAPSHOTINTERFACE_H
