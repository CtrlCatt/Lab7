#ifndef NPC_H
#define NPC_H
#include <string>
#include <cmath>
class NPC {
protected:
    std::string name;
    int x, y;
    int moveDistance, killDistance;
    bool alive;
public:
    NPC(const std::string& name, int x, int y, int moveDist, int killDist)
        : name(name), x(x), y(y), moveDistance(moveDist), killDistance(killDist), alive(true) {}
    virtual ~NPC() = default;
    const std::string& getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getMoveDistance() const { return moveDistance; }
    int getKillDistance() const { return killDistance; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    void move(int dx, int dy);
    virtual std::string getType() const = 0;
    virtual bool canKill(const NPC& other) const = 0;
};
#endif // NPC_H
