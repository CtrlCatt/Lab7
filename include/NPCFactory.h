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
            return std::make_unique<SlaveTrader>(name, x, y, 10, 10); // moveDistance = 10, killDistance = 10
        } else if (type == "Squirrel") {
            return std::make_unique<Squirrel>(name, x, y, 5, 5); // moveDistance = 5, killDistance = 5
        } else if (type == "Knight") {
            return std::make_unique<Knight>(name, x, y, 30, 10); // moveDistance = 30, killDistance = 10
        }
        throw std::invalid_argument("Unknown NPC type");
    }
};
#endif // NPCFACTORY_H
