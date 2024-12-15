#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H
#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include <algorithm>
class BattleSystem {
    std::vector<std::unique_ptr<Observer>> observers;
public:
    void addObserver(std::unique_ptr<Observer> observer) {
        observers.push_back(std::move(observer));
    }
    void battle(std::vector<std::unique_ptr<NPC>>& npcs, int range) {
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (npcs[i] && npcs[j]) {
                    int dx = npcs[i]->getX() - npcs[j]->getX();
                    int dy = npcs[i]->getY() - npcs[j]->getY();
                    if (std::sqrt(dx * dx + dy * dy) <= range) {
                        if (npcs[i]->canKill(*npcs[j])) {
                            notify(*npcs[i], *npcs[j]);
                            npcs[j].reset();
                        } else if (npcs[j]->canKill(*npcs[i])) {
                            notify(*npcs[j], *npcs[i]);
                            npcs[i].reset();
                        }
                    }
                }
            }
        }
        npcs.erase(std::remove(npcs.begin(), npcs.end(), nullptr), npcs.end());
    }
private:
    void notify(const NPC& killer, const NPC& victim) {
        for (const auto& observer : observers) {
            observer->onKill(killer, victim);
        }
    }
};
#endif // BATTLESYSTEM_H
