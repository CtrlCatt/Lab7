#ifndef SQUIRREL_H
#define SQUIRREL_H
#include "NPC.h"
class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override { return "Squirrel"; }
    bool canKill(const NPC& other) const override { return other.getType() == "Squirrel"; }
};
#endif // SQUIRREL_H
