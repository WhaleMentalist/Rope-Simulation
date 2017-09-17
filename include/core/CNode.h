#ifndef PHYSICS_ENGINE_CNODE_H
#define PHYSICS_ENGINE_CNODE_H

class CNode
{
    public:

        virtual void simulate(float deltaTime) = 0;

    private:

        virtual void solve() = 0;

};

#endif //PHYSICS_ENGINE_CNODE_H
