#include "include/BattleSystem.h"
#include "include/NPCFactory.h"
#include "include/ConsoleLogger.h"
#include "include/FileLogger.h"
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <random>

std::vector<std::unique_ptr<NPC>> npcs;
std::shared_mutex npcMutex;

// Поток 1: перемещение NPC
void moveNPCs() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::unique_lock lock(npcMutex);
        for (auto& npc : npcs) {
            if (npc && npc->isAlive()) {
                npc->move(rand() % npc->getMoveDistance(), rand() % npc->getMoveDistance());
            }
        }
    }
}

// Поток 2: бои NPC
void battleNPCs() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::unique_lock lock(npcMutex);
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (npcs[i] && npcs[j] && npcs[i]->isAlive() && npcs[j]->isAlive()) {
                    int dx = npcs[i]->getX() - npcs[j]->getX();
                    int dy = npcs[i]->getY() - npcs[j]->getY();
                    if (std::sqrt(dx * dx + dy * dy) <= npcs[i]->getKillDistance()) {
                        // Симуляция боя с кубиком
                        int attack = rand() % 6 + 1;
                        int defense = rand() % 6 + 1;
                        if (attack > defense) {
                            npcs[j]->kill();
                        }
                    }
                }
            }
        }
    }
}

// Главный поток: отображение карты
void printMap() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::shared_lock lock(npcMutex);
        std::cout << "Current Map State:\n";
        for (const auto& npc : npcs) {
            if (npc && npc->isAlive()) {
                std::cout << npc->getType() << " (" << npc->getName() << ") at (" 
                          << npc->getX() << ", " << npc->getY() << ")\n";
            }
        }
    }
}

int main() {
    srand(time(nullptr));

    // Генерация 50 случайных NPC
    const std::vector<std::string> npcTypes = {"SlaveTrader", "Squirrel", "Knight"};
    for (int i = 0; i < 50; ++i) {
        std::string type = npcTypes[rand() % npcTypes.size()]; // Случайный выбор типа
        std::string name = type + std::to_string(i); // Уникальное имя NPC
        int x = rand() % 100; // Случайная координата X
        int y = rand() % 100; // Случайная координата Y
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
    }

    std::thread movementThread(moveNPCs);
    std::thread battleThread(battleNPCs);
    std::thread printThread(printMap);

    std::this_thread::sleep_for(std::chrono::seconds(30));

    {
        std::shared_lock lock(npcMutex);
        std::cout << "\nGame Over! Surviving NPCs:\n";
        for (const auto& npc : npcs) {
            if (npc && npc->isAlive()) {
                std::cout << npc->getType() << " (" << npc->getName() << ") survived.\n";
            }
        }
    }

    movementThread.detach();
    battleThread.detach();
    printThread.detach();

    return 0;
}
