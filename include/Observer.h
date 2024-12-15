#ifndef OBSERVER_H
#define OBSERVER_H
#include "NPC.h"
class Observer {
public:
    virtual void onKill(const NPC& killer, const NPC& victim) = 0;
    virtual ~Observer() = default;
};
#endif // OBSERVER_H
