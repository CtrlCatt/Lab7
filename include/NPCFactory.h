#ifndef NPCFACTORY_H
#define NPCFACTORY_H
#include "SlaveTrader.h"
#include "Squirrel.h"
#include "Knight.h"
#include <stdexcept>
#include <memory>
#include <string>
class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y) {
        if (type == "SlaveTrader") {
            return std::make_unique<SlaveTrader>(name, x, y);
        } else if (type == "Squirrel") {
            return std::make_unique<Squirrel>(name, x, y);
        } else if (type == "Knight") {
            return std::make_unique<Knight>(name, x, y);
        }
        throw std::invalid_argument("Unknown NPC type");
    }
};
#endif // NPCFACTORY_H
