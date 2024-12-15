#ifndef NPC_H
#define NPC_H
#include <string>
#include <cmath>
class NPC {
protected:
    std::string name;
    int x, y;
public:
    NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    virtual ~NPC() = default;
    const std::string& getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    virtual std::string getType() const = 0;
    virtual bool canKill(const NPC& other) const = 0;
};
#endif // NPC_H
