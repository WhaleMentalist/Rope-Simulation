#ifndef PHYSICS_ENGINE_SPRING_H
#define PHYSICS_ENGINE_SPRING_H

#include "CNode.h"
#include "PNode.h"

class Spring : public CNode
{
    public:

        Spring(float stiffness, float dampening, float restLength,
                PNode* p1, PNode* p2);

        void simulate(float deltaTime) override;

    private:

        void solve() override;

        const static unsigned int NUM_POINTS = 2;

        float _k;

        float _kd;

        float _restLength;

        PNode* _endPoints[NUM_POINTS];
};

#endif //PHYSICS_ENGINE_SPRING_H
