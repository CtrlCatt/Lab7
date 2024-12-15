#include "include/BattleSystem.h"
#include "include/NPCFactory.h"
#include "include/ConsoleLogger.h"
#include "include/FileLogger.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<NPC>> npcs;
    BattleSystem battleSystem;
    battleSystem.addObserver(std::make_unique<ConsoleLogger>());
    battleSystem.addObserver(std::make_unique<FileLogger>());

    // Example setup
    npcs.push_back(NPCFactory::createNPC("SlaveTrader", "Trader1", 200, 200));
    npcs.push_back(NPCFactory::createNPC("Knight", "Knight1", 205, 205));
    npcs.push_back(NPCFactory::createNPC("Squirrel", "Squirrel1", 120, 100));
    npcs.push_back(NPCFactory::createNPC("Squirrel", "Squirrel2", 130, 100));
    npcs.push_back(NPCFactory::createNPC("SlaveTrader", "Trader2", 250, 250));
    npcs.push_back(NPCFactory::createNPC("Knight", "Knight2", 255, 255));
    npcs.push_back(NPCFactory::createNPC("Squirrel", "Squirrel3", 140, 110));
    npcs.push_back(NPCFactory::createNPC("SlaveTrader", "Trader3", 300, 300));
    npcs.push_back(NPCFactory::createNPC("Squirrel", "Squirrel4", 400, 400));
    npcs.push_back(NPCFactory::createNPC("Knight", "Knight3", 305, 305));



    // Print NPCs
    std::cout << "Initial NPCs:\n";
    for (const auto& npc : npcs) {
        std::cout << npc->getType() << " (" << npc->getName() << ") at (" << npc->getX() << ", " << npc->getY() << ")\n";
    }

    // Start battle
    std::cout << "\nBattle starts:\n";
    battleSystem.battle(npcs, 50);

    // Print remaining NPCs
    std::cout << "\nRemaining NPCs:\n";
    for (const auto& npc : npcs) {
        std::cout << npc->getType() << " (" << npc->getName() << ") at (" << npc->getX() << ", " << npc->getY() << ")\n";
    }

    return 0;
}