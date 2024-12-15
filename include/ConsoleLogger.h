#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H
#include "Observer.h"
#include <iostream>
class ConsoleLogger : public Observer {
public:
    void onKill(const NPC& killer, const NPC& victim) override {
        std::cout << killer.getType() << " (" << killer.getName() << ") killed "
                  << victim.getType() << " (" << victim.getName() << ")\n";
    }
};
#endif // CONSOLELOGGER_H
