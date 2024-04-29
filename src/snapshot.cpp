#include "snapshot.h"

Snapshot::Snapshot() : Snapshot("") {}

Snapshot::Snapshot(std::string data) : data(data) {}

std::string Snapshot::getData() const { return data; }

void Snapshot::setData(std::string data) { this->data = data; }
