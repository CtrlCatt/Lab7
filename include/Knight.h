#ifndef KNIGHT_H
#define KNIGHT_H
#include "NPC.h"
class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override { return "Knight"; }
    bool canKill(const NPC& other) const override { return other.getType() == "SlaveTrader"; }
};
#endif // KNIGHT_H
