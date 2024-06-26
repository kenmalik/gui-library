#ifndef CS8_GUILIBRARY_SNAPSHOT_H
#define CS8_GUILIBRARY_SNAPSHOT_H

#include <string>

class Snapshot {
  public:
    Snapshot();
    Snapshot(std::string data);
    std::string getData() const;
    void setData(std::string data);

  private:
    std::string data;
};

#endif // CS8_GUILIBRARY_SNAPSHOT_H
