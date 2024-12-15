#ifndef FILELOGGER_H
#define FILELOGGER_H
#include "Observer.h"
#include <fstream>
class FileLogger : public Observer {
    std::ofstream logFile;
public:
    FileLogger() : logFile("log.txt", std::ios::app) {}
    ~FileLogger() { if (logFile.is_open()) logFile.close(); }
    void onKill(const NPC& killer, const NPC& victim) override {
        if (logFile.is_open()) {
            logFile << killer.getType() << " (" << killer.getName() << ") killed "
                    << victim.getType() << " (" << victim.getName() << ")\n";
        }
    }
};
#endif // FILELOGGER_H
