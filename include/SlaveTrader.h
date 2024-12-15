#ifndef SLAVETRADER_H
#define SLAVETRADER_H
#include "NPC.h"
class SlaveTrader : public NPC {
public:
    SlaveTrader(const std::string& name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override { return "SlaveTrader"; }
    bool canKill(const NPC& other) const override { return other.getType() == "Squirrel"; }
};
#endif // SLAVETRADER_H
